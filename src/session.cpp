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

Requests::Response Requests::Session::send(const Request &r)
{
    // Set up an HTTP request message
    http::request<http::string_body> beast_req {
        static_cast<http::verb>(r.method.to_enum()),
        r.target,
        11,
        r.body
    };

    /* Set up headers */
    for (const auto &[h, v] : common_headers)
    {
        beast_req.set(static_cast<http::field>(h.to_enum()), v);
    }
    for (const auto &[h, v] : r.headers)
    {
        beast_req.set(static_cast<http::field>(h.to_enum()), v);
    }
    beast_req.set(http::field::host, host + ":" + std::to_string(port));



    // This buffer is used for reading and must be persisted
    beast::flat_buffer buffer;

    // Declare a container to hold the response
    http::response<http::string_body> beast_res;

    // The io_context is required for all I/O
    net::io_context ioc;


    // Look up the domain name
    tcp::resolver resolver(ioc);
    const auto results = resolver.resolve(host, std::to_string(port));


    // Make the connection on the IP address we get from a lookup
    beast::tcp_stream tcp_stream(ioc);
    tcp_stream.connect(results);


    if (scheme == Url::Scheme::http)
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
        if(!SSL_set_tlsext_host_name(ssl_stream.native_handle(), host.c_str()))
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



    /* Convert to our response */
    Response res {
        .body = beast_res.body(),
        .headers = {},
        .reason = beast_res.reason().to_string(),
        .status_code = static_cast<uint16_t>(beast_res.result_int())
    };
    for (const auto &e : beast_res)
    {
        res.headers[static_cast<Header::enum_t>(e.name())] = e.value().to_string();
    }

    return res;
};