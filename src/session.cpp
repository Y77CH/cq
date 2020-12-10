#include "requests/session.hpp"

#include <deque>
#include <variant>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>

#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>

namespace beast = boost::beast;
namespace http  = beast::http;
namespace net   = boost::asio;
namespace ssl   = net::ssl;

using tcp = net::ip::tcp;


struct Requests::Session::Impl
{
    // The io_context is required for all I/O
    net::io_context io_ctx {};
    // Context for SSL
    ssl::context ssl_ctx {ssl::context::tlsv12_client};

    // One of possible streams
    std::variant<
        beast::tcp_stream,
        beast::ssl_stream<beast::tcp_stream>
    > stream { beast::tcp_stream{io_ctx} };
};


Requests::Session::Session(const Url &base_url, const Headers &common_headers)
    : pimpl(new Impl()), base_url(base_url), common_headers(common_headers)
{
    /* Set up port */
    std::string port = base_url.port;
    if (port.empty())
    {
        if (base_url.scheme == "http") { port = "80"; }
        else { port = "443"; } // HTTPS by default
    }

    // Look up the domain name
    tcp::resolver resolver(pimpl->io_ctx);
    const auto results = resolver.resolve(base_url.host, port);

    // Make a TCP connection
    auto &&tcp_stream = std::get<beast::tcp_stream>(pimpl->stream);
    tcp_stream.connect(results);

    // HTTPS by default
    if (base_url.scheme != "http")
    {
        // Find certificates in default paths
        pimpl->ssl_ctx.set_default_verify_paths();

        // Verify the remote server's certificate
        pimpl->ssl_ctx.set_verify_mode(ssl::verify_peer);

        beast::ssl_stream<beast::tcp_stream> ssl_stream(tcp_stream.release_socket(), pimpl->ssl_ctx);

        // Set SNI Hostname (many hosts need this to handshake successfully)
        if(!SSL_set_tlsext_host_name(ssl_stream.native_handle(), base_url.host.c_str()))
        {
            beast::error_code ec{static_cast<int>(::ERR_get_error()), net::error::get_ssl_category()};
            throw beast::system_error{ec};
        }

        // Perform the SSL handshake
        ssl_stream.handshake(ssl::stream_base::client);

        // Change stream
        pimpl->stream = std::move(ssl_stream);
    }
}


Requests::Response Requests::Session::send(Request r)
{
    /* Update info in the request */
    r.version = "HTTP/1.1";
    r.target.scheme = "";
    r.target.host = "";
    r.target.port = "";
    for (const auto &[h, v] : common_headers) { r.headers[h] = v; }
    r.headers["host"] = base_url.host;

    // Set up an HTTP request message
    http::request<http::string_body> beast_req {
        static_cast<http::verb>(r.method.to_enum()),
        r.target.to_string(),
        11,
        r.body
    };
    beast_req.prepare_payload();

    /* Set up headers */
    for (const auto &[h, v] : r.headers) { beast_req.set(h, v); }
    beast_req.set(
        http::field::host,
        base_url.host + (base_url.port.empty() ? "" : ":") + base_url.port
    );



    // This buffer is used for reading and must be persisted
    beast::flat_buffer buffer;

    // Declare a container to hold the response
    http::response<http::string_body> beast_res;

    // HTTPS by default
    if (base_url.scheme != "http")
    {
        // Send the HTTP request to the remote host
        http::write(std::get<beast::ssl_stream<beast::tcp_stream>>(pimpl->stream), beast_req);

        // Receive the HTTP response
        http::read(std::get<beast::ssl_stream<beast::tcp_stream>>(pimpl->stream), buffer, beast_res);
    }
    else
    {
        // Send the HTTP request to the remote host
        http::write(std::get<beast::tcp_stream>(pimpl->stream), beast_req);

        // Receive the HTTP response
        http::read(std::get<beast::tcp_stream>(pimpl->stream), buffer, beast_res);
    }


    Url response_url {base_url};
    response_url.path = r.target.path;
    response_url.query = r.target.query;
    response_url.fragment = r.target.fragment;

    /* Convert to our response */
    Response res {
        .headers = {},
        .history = {},
        .reason = beast_res.reason().to_string(),
        .request = r,
        .status_code = static_cast<uint16_t>(beast_res.result_int()),
        .text = beast_res.body(),
        .url = response_url
    };
    for (const auto &e : beast_res)
    {
        res.headers[e.name_string().to_string()] = e.value().to_string();
    }

    return res;
};


constexpr const size_t max_open_sessions_count = 5;
std::deque<Requests::Session> open_sessions;


Requests::Session & Requests::get_session(const Url &base_url, const Headers &common_headers)
{
    // Find existing session
    for (auto &session : open_sessions)
    {
        // Port of existing session
        std::string port1 = session.base_url.port;
        if (port1.empty())
        {
            if (session.base_url.scheme == "http") { port1 = "80"; }
            else { port1 = "443"; } // HTTPS by default
        }

        // Other port
        std::string port2 = base_url.port;
        if (port2.empty())
        {
            if (base_url.scheme == "http") { port2 = "80"; }
            else { port2 = "443"; } // HTTPS by default
        }

        // If equivalent connections
        if (
            (session.base_url.scheme == base_url.scheme) &&
            (session.base_url.host == base_url.host) &&
            (port1 == port2)
        )
        {
            return session;
        }
    }

    open_sessions.emplace_front(base_url, common_headers);

    if (open_sessions.size() > max_open_sessions_count)
    {
        open_sessions.pop_back();
    }

    return open_sessions.front();
}

