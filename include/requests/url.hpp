#ifndef REQUESTS_URL_HPP
#define REQUESTS_URL_HPP

#include <string>
#include <string_view>

namespace requests {

// Uniform Resource Locators [RFC1738]
struct url
{
    // Allow empty URLs
    url();

    // Note: we allow implicit conversion to URL
    url(std::string_view url);

    std::string scheme;
    std::string host;
    uint16_t    port;
    std::string path;
    std::string query;
    std::string fragment;
};

} // namespace requests

#endif // REQUESTS_URL_HPP