#ifndef REQUESTS_REQUEST_HPP
#define REQUESTS_REQUEST_HPP

#include <string>
#include <vector>

#include "requests/options.hpp"


namespace Requests {

class Request
{
public:
    Method      method;
    std::string target;
    uint16_t    version;
    Headers     headers;
    std::string body;


    /* Helper setters */
    void set(const Headers &hs) noexcept { headers = hs; }
    void set(const Query   &q)
    {
        target += "?";
        for (const auto &[k, v] : q)
        {
            target += k + "=" + v + "&";
        }
        target.pop_back();
    }
    void set(const Fragment &f) { if (!f.empty()) { target += "#" + f; } }
    void set(const Text &t) { headers["content-type"] = "text/plain"; body = t; }
    void set(const Json &j) { headers["content-type"] = "application/json"; body = j; }
    void set(const Data &d)
    {
        headers["content-type"] = "application/x-www-form-urlencoded";
        for (const auto &[k, v] : d)
        {
            body += k + "=" + v + "&";
        }
        body.pop_back();
    }
};

} // namespace Requests

#endif // REQUESTS_REQUEST_HPP