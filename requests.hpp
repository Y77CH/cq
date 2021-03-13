#pragma once

#include <bitset>
#include <map>
#include <regex>
#include <string>
#include <string_view>

#include <curl/curl.h>

#ifdef REQUESTS_WITH_NLOHMANN_JSON
    #include "nlohmann.hpp"
#endif // REQUESTS_WITH_NLOHMANN_JSON

namespace requests {

// Requested URL.
struct url
{
    /* Origin */
    std::string scheme; // http or https (or empty)
    std::string host;   // Can't be empty, if port or scheme not empty
    std::string port;   // In range [0, 65535]

    /* Resource */
    std::string path;     // With leading '/' (if not empty)
    std::string query;    // Without '?'
    std::string fragment; // Without '#'


    /* Create URL from string */
    url(const char *str) noexcept : url(std::string_view{str}) {}
    url(const std::string &str) noexcept : url(std::string_view{str}) {}
    url(std::string_view url = "") noexcept
    {
        std::cmatch match;

        // Starts with http(s) followed by :// in any case
        std::regex rscheme("^(https?)://", std::regex_constants::icase);

        // Find scheme
        if (std::regex_search(url.data(), match, rscheme))
        {
            // Get scheme without ://
            scheme = match.str(1);
            // Convert scheme to lowercase
            std::ranges::transform(scheme, scheme.begin(), [](char c){ return std::tolower(c); });
            // Remove found
            url.remove_prefix(match.str().size());
        }


        /* Regex helpers */
        const std::string hostnumber  {"(([0-9]{1,3}\\.){3}[0-9]{1,3})"};
        const std::string toplabel    {"([a-z][-a-z0-9]*[a-z0-9])"};
        const std::string domainlabel {"([a-z0-9][-a-z0-9]*[a-z0-9])"};
        const std::string hostname    {"((" + domainlabel + "\\.)*" + toplabel + ")"};

        // Starts with valid host
        std::regex rhost(
            "^(" + hostname + "|" + hostnumber + ")",
            std::regex_constants::icase | std::regex_constants::nosubs
        );

        // Find host
        if (std::regex_search(url.data(), match, rhost))
        {
            // Get host
            host = match.str();
            // Convert host to lowercase
            std::ranges::transform(host, host.begin(), [](char c){ return std::tolower(c); });
            // Remove found
            url.remove_prefix(match.str().size());
        }


        // Starts with optional port
        std::regex rport("^(:([0-9]{1,5}))?");

        // Find port
        std::regex_search(url.data(), match, rport);
        if (!match.str().empty())
        {
            // Get specified port
            port = match.str(2);
            // Remove found
            url.remove_prefix(match.str().size());
        }


        /* Regex helpers */
        const std::string escape   {"(%[0-9a-f]{2})"};
        const std::string hsegment {"(([-$_.+;:@&=!*'(),a-z0-9]|" + escape + ")*)"};

        // Starts with optional path
        std::regex rpath(
            "^(/" + hsegment + ")*",
            std::regex_constants::icase | std::regex_constants::nosubs
        );

        // Find path
        std::regex_search(url.data(), match, rpath);
        // Get specified path or ""
        path = match.str();
        // Remove found
        url.remove_prefix(match.str().size());


        // Starts with optional query
        std::regex rquery("^(?:\\?" + hsegment + ")?", std::regex_constants::icase);

        // Find query
        std::regex_search(url.data(), match, rquery);
        // Get specified query or ""
        query = match.str(1);
        // Remove found
        url.remove_prefix(match.str().size());


        // Starts with optional query
        std::regex rfragment("^(?:#" + hsegment + ")?", std::regex_constants::icase);

        // Find query
        std::regex_search(url.data(), match, rfragment);
        // Get specified query or ""
        fragment = match.str(1);
        // Remove found
        url.remove_prefix(match.str().size());
    }


    // [<scheme>://]<host>[:<port>]
    std::string origin() const noexcept
    {
        if (host.empty()) { return ""; }

        std::string host_port = host;
        if (!port.empty()) { host_port += ":" + port; }

        if (scheme.empty()) { return host_port; }
        return scheme + "://" + host_port;
    }

    // <path>[?<query>][#<fragment>]
    std::string resource() const noexcept
    {
        std::string res = path;

        if (path.empty() && (!query.empty() || !fragment.empty())) { res += "/"; }
        if (!query.empty())    { res += "?" + query; }
        if (!fragment.empty()) { res += "#" + fragment; }

        return res;
    }

    // Return URL string
    std::string to_string() const noexcept { return origin() + resource(); }
};

// URL query part (?)
struct query : std::map<std::string, std::string>
{
    using std::map<std::string, std::string>::map;
};

// URL fragment part (#)
struct fragment : std::string
{
    using std::string::string;
};

std::string urlencoded(const std::map<std::string, std::string> &kv)
{
    std::string res;
    for (const auto &[k, v] : kv)
    {
        res += k + "=" + v + "&";
    }
    if (!res.empty()) { res.pop_back(); }
    return res;
}

std::map<std::string, std::string> urldecoded(std::string_view str)
{
    std::map<std::string, std::string> res;

    std::string k, v;
    bool processing_k = true;
    for (const auto &c : str)
    {
        if (c == '=') { processing_k = false; continue; }
        if (c == '&') { res[k] = v; k = v = ""; processing_k = true; continue; }
        if (processing_k) { k.push_back(c); }
        else { v.push_back(c); }
    }
    if (!k.empty()) { res[k] = v; }

    return res;
}

// Basic authorization
struct auth
{
    std::string username;
    std::string password;

    std::string to_base64() const noexcept
    {
        constexpr std::string_view base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                                "abcdefghijklmnopqrstuvwxyz"
                                                                "0123456789+/";

        std::string msg = username + ":" + password;
        std::string_view str = msg;

        std::string res; res.reserve(str.size() * 1.33);

        while (str.size() >= 3)
        {
            std::string bits; bits.reserve(24);
            for (size_t i = 0; i < 3; ++i)
            {
                bits += std::bitset<8>{static_cast<unsigned long long>(str[i])}.to_string();
            }

            for (size_t i = 0; i < 4; ++i)
            {
                res += base64_chars[std::bitset<6>(bits, i*6).to_ulong()];
            }

            str.remove_prefix(3);
        }

        if (str.size() == 2)
        {
            std::string bits; bits.reserve(18);
            for (size_t i = 0; i < 2; ++i)
            {
                bits += std::bitset<8>{static_cast<unsigned long long>(str[i])}.to_string();
            }
            bits += "00";

            for (size_t i = 0; i < 3; ++i)
            {
                res += base64_chars[std::bitset<6>(bits, i*6).to_ulong()];
            }
            res += "=";
        }
        else if (str.size() == 1)
        {
            std::string bits {std::bitset<8>{static_cast<unsigned long long>(str[0])}.to_string() + "0000"};

            for (size_t i = 0; i < 2; ++i)
            {
                res += base64_chars[std::bitset<6>(bits, i*6).to_ulong()];
            }
            res += "==";
        }

        return res;
    }
};

// Bearer token authorization
struct bearer
{
    std::string token;
};

// Single HTTP-header
struct header
{
    std::string name;
    std::string value;

    std::string to_string() const { return name + ": " + value; }

    static header parse(std::string_view str)
    {
        header res;
        std::cmatch match;
        std::regex r("(.*): (.*)");
        if (std::regex_search(str.data(), match, r))
        {
            res.name = match.str(1);
            res.value = match.str(2);
        }
        return res;
    }
};


namespace comparators {

struct case_insensitive_less
{
    constexpr bool operator()(std::string_view lhs, std::string_view rhs) const noexcept
    {
        if (lhs.size() < rhs.size()) { return true; }
        if (lhs.size() > rhs.size()) { return false; }

        for (size_t i = 0; i < lhs.size(); ++i)
        {
            if (std::tolower(lhs[i]) < std::tolower(rhs[i])) { return true; }
            if (std::tolower(lhs[i]) > std::tolower(rhs[i])) { return false; }
        }

        return false;
    }
};

} // namespace Comparators

// Multiple HTTP-headers
struct headers : std::map<std::string, std::string, comparators::case_insensitive_less>
{
    using std::map<std::string, std::string, comparators::case_insensitive_less>::map;

    void insert(const header &h) { map::insert({h.name, h.value}); }
};

// URL-encoded data
struct data : std::map<std::string, std::string>
{
    using std::map<std::string, std::string>::map;
};

#ifdef REQUESTS_WITH_NLOHMANN_JSON
// JSON data
using json = nlohmann::json;
#else
// JSON data
struct json : std::string
{
    using std::string::string;
};
#endif // REQUESTS_WITH_NLOHMANN_JSON

// Plain text
struct text : std::string
{
    using std::string::string;
};


namespace concepts {

// One of Request's options
template<typename T>
concept option = std::same_as<T, auth>     ||
                 std::same_as<T, data>     ||
                 std::same_as<T, fragment> ||
                 std::same_as<T, header>   ||
                 std::same_as<T, headers>  ||
                 std::same_as<T, json>     ||
                 std::same_as<T, query>    ||
                 std::same_as<T, text>;

} // namespace concepts

// Request's method
enum class method {
    DELETE,
    GET,
    HEAD,
    POST,
    PUT,
    OPTIONS,
    PATCH,
};

struct request
{
    requests::method  method;
    requests::url     target;
    requests::headers headers;
    std::string body;


    /* Helper setters */
    template<concepts::option T, concepts::option ...Ts>
    void set(const T &t, const Ts & ...ts) noexcept { set(t); set(ts...); }
    void set() noexcept {}

    void set(const requests::headers &hs) noexcept { headers = hs; }
    void set(const query    &q) noexcept { target.query = urlencoded(q); }
    void set(const fragment &f) noexcept { target.fragment = f; }
    void set(const auth     &a) noexcept { headers["authorization"] = "Basic " + a.to_base64(); }
    void set(const bearer   &b) noexcept { headers["authorization"] = "Bearer " + b.token; }
    void set(const header   &h) noexcept { headers[h.name] = h.value; }
    void set(const text &t) noexcept { body = t; headers["content-type"] = "text/plain"; }
    void set(const data &d) noexcept
    {
        body = urlencoded(d);
        headers["content-type"] = "application/x-www-form-urlencoded";
    }
    void set(const json &j) noexcept
    {
    #ifdef REQUESTS_WITH_NLOHMANN_JSON
        body = nlohmann::to_string(j);
    #else
        body = j;
    #endif // REQUESTS_WITH_NLOHMANN_JSON
        headers["content-type"] = "application/json";
    }
};

struct response
{
    unsigned          status_code = 0;
    std::string       reason;
    requests::headers headers;
    std::string       text;

#ifdef REQUESTS_WITH_NLOHMANN_JSON
    requests::json json() const { return nlohmann::json::parse(text); }
#endif // REQUESTS_WITH_NLOHMANN_JSON
};


namespace detail {

size_t write_callback(char *buffer, size_t size, size_t nitems, void *r)
{
    static_cast<response *>(r)->text.append(static_cast<char*>(buffer), size * nitems);
    return size * nitems;
}

size_t header_callback(char *buffer, size_t size, size_t nitems, void *r)
{
    std::string_view str(buffer, size * nitems - 2);
    if (str.starts_with("HTTP"))
    {
        static_cast<response *>(r)->reason = str.substr(13);
    }
    else if (!str.empty())
    {
        static_cast<response *>(r)->headers.insert(header::parse(str));
    }
    return size * nitems;
}

class curl_holder
{
public:
    static curl_holder & get()
    {
        static curl_holder ch;
        return ch;
    }

    curl_holder(const curl_holder &) = delete;
    void operator=(const curl_holder &) = delete;

    CURL * handler() const { return handler_; }

    ~curl_holder()
    {
        curl_easy_cleanup(handler_);
        curl_global_cleanup();
    }

private:
    curl_holder()
    {
        curl_global_init(CURL_GLOBAL_DEFAULT);

        handler_ = curl_easy_init();

        auto info = curl_version_info(CURLVERSION_NOW);
        std::string version = "curl/" + std::string{info->version};
        curl_easy_setopt(handler_, CURLOPT_USERAGENT, version.c_str());
        curl_easy_setopt(handler_, CURLOPT_TCP_KEEPALIVE, 1L);
        curl_easy_setopt(handler_, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(handler_, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(handler_, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(handler_, CURLOPT_HEADERFUNCTION, header_callback);
        curl_easy_setopt(handler_, CURLOPT_CAINFO, "/etc/ssl/certs/ca-certificates.crt");
    }

    CURL *handler_ = nullptr;
};

} // namespace detail

// Single connection session
struct session
{
    url origin; // scheme, host and port
    headers common_headers = {}; // Added to each request

    response send(request r)
    {
        response res;

        /* Update info in the request */
        for (const auto &[h, v] : common_headers) { r.headers[h] = v; }
        r.headers["host"] = origin.host;


        CURL *curl = detail::curl_holder::get().handler();

        switch (r.method)
        {
        case method::DELETE:  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");  break;
        case method::GET:     curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);              break;
        case method::HEAD:    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "HEAD");    break;
        case method::POST:
            curl_easy_setopt(curl, CURLOPT_POST, 1L);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, r.body.c_str());
            break;
        case method::PUT:     curl_easy_setopt(curl, CURLOPT_PUT, 1L);                  break;
        case method::OPTIONS: curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "OPTIONS"); break;
        case method::PATCH:   curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");   break;
        }

        std::string url = origin.origin() + r.target.resource();
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        curl_slist *curl_headers = nullptr;
        for (const auto &[h, v] : r.headers)
        {
            curl_headers = curl_slist_append(curl_headers, (h + ": " + v).c_str());
        }
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_headers);


        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &res);

        curl_easy_setopt(curl, CURLOPT_WRITEDATA,  &res);

        curl_easy_perform(curl);
        curl_slist_free_all(curl_headers);

        long response_code;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

        res.status_code = static_cast<unsigned>(response_code);

        return res;
    }

    template<concepts::option ...Args>
    response delet(const url &target, const Args & ...args)
    {
        return send(construct_request(method::DELETE, target, args...));
    }

    template<concepts::option ...Args>
    response get(const url &target, const Args & ...args)
    {
        return send(construct_request(method::GET, target, args...));
    }

    template<concepts::option ...Args>
    response head(const url &target, const Args & ...args)
    {
        return send(construct_request(method::HEAD, target, args...));
    }

    template<concepts::option ...Args>
    response options(const url &target, const Args & ...args)
    {
        return send(construct_request(method::OPTIONS, target, args...));
    }

    template<concepts::option ...Args>
    response patch(const url &target, const Args & ...args)
    {
        return send(construct_request(method::PATCH, target, args...));
    }

    template<concepts::option ...Args>
    response post(const url &target, const Args & ...args)
    {
        return send(construct_request(method::POST, target, args...));
    }

    template<concepts::option ...Args>
    response put(const url &target, const Args & ...args)
    {
        return send(construct_request(method::PUT, target, args...));
    }

private:
    template<concepts::option ...Args>
    request construct_request(method m, const url &target, const Args & ...args) const
    {
        request r{ m, target, {{"user-agent", "requests"}}, "" };
        r.set(args...);
        return r;
    }
};


template<concepts::option ...Args>
response delet(const url &url, const Args &...args)   { return session{url}.delet(url, args...); }

template<concepts::option ...Args>
response get(const url &url, const Args &...args)     { return session{url}.get(url, args...); }

template<concepts::option ...Args>
response head(const url &url, const Args &...args)    { return session{url}.head(url, args...); }

template<concepts::option ...Args>
response options(const url &url, const Args &...args) { return session{url}.options(url, args...); }

template<concepts::option ...Args>
response patch(const url &url, const Args &...args)   { return session{url}.patch(url, args...); }

template<concepts::option ...Args>
response post(const url &url, const Args &...args)    { return session{url}.post(url, args...); }

template<concepts::option ...Args>
response put(const url &url, const Args & ...args)    { return session{url}.put(url, args...); }

} // namespace requests