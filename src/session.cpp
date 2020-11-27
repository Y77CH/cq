#include "requests/session.hpp"

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

    // The io_context is required for all I/O
    net::io_context ioc;


    /* Set up port */
    std::string port = base_url.port;
    if (port.empty())
    {
        if (base_url.scheme == "http") { port = "80"; }
        else { port = "443"; }
    }


    // Look up the domain name
    tcp::resolver resolver(ioc);
    const auto results = resolver.resolve(base_url.host, port);


    // Make the connection on the IP address we get from a lookup
    beast::tcp_stream tcp_stream(ioc);
    tcp_stream.connect(results);


    if (base_url.scheme == "http")
    {

        // Send the HTTP request to the remote host
        http::write(tcp_stream, beast_req);

        // Receive the HTTP response
        http::read(tcp_stream, buffer, beast_res);

    }
    else
    {
        // The SSL context is required, and holds certificates
        ssl::context ctx(ssl::context::tlsv12_client);

        // Find certificates in default paths
        ctx.set_default_verify_paths();

        // Verify the remote server's certificate
        ctx.set_verify_mode(ssl::verify_peer);

        beast::ssl_stream<beast::tcp_stream> ssl_stream(tcp_stream.release_socket(), ctx);

        // Set SNI Hostname (many hosts need this to handshake successfully)
        if(!SSL_set_tlsext_host_name(ssl_stream.native_handle(), base_url.host.c_str()))
        {
            beast::error_code ec{static_cast<int>(::ERR_get_error()), net::error::get_ssl_category()};
            throw beast::system_error{ec};
        }

        // Perform the SSL handshake
        ssl_stream.handshake(ssl::stream_base::client);


        // Send the HTTP request to the remote host
        http::write(ssl_stream, beast_req);

        // Receive the HTTP response
        http::read(ssl_stream, buffer, beast_res);
    }


    Url response_url {base_url};
    response_url.path = r.target.path;
    response_url.query = r.target.query;
    response_url.fragment = r.target.fragment;

    /* Convert to our response */
    Response res {
        .encoding = "",
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