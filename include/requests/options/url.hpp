#ifndef REQUESTS_OPTIONS_URL_HPP
#define REQUESTS_OPTIONS_URL_HPP

#include <string>
#include <string_view>


namespace Requests {

struct Url
{
    std::string scheme; // HTTP or HTTPS. Without "://"
    std::string host;
    std::string port;   // In range [0, 65535]
    std::string path;
    std::string query;
    std::string fragment;


    Url() = default;

    // Create URL from string
    Url(const char *url) noexcept : Url(std::string_view{url}) {}

    // Create URL from string
    Url(std::string_view url) noexcept;


    // Return URL string
    std::string to_string() const noexcept;
};

} // namespace Requests

#endif // REQUESTS_OPTIONS_URL_HPP