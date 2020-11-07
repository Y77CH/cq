#ifndef REQUESTS_URL_HPP
#define REQUESTS_URL_HPP

#include <string>

#include "requests/enums.hpp"

namespace requests {

// Uniform Resource Locators [RFC1738]
struct url
{
private:
    // Inheritable enum class
    struct scheme_helper {
        // Possible schemes
        enum enum_t {
            http  = 80,
            https = 443
        };
    };

public:
    // Scheme enum wrapper
    struct scheme_t : public scheme_helper,
                      public enums::enum_wrapper<scheme_helper::enum_t, enums::case_insensitive>
    { using enums::enum_wrapper<scheme_helper::enum_t, enums::case_insensitive>::enum_wrapper; };


    // Create URL from string
    explicit url(std::string_view url);


    // Return URL string
    [[nodiscard]] std::string as_string() const noexcept;


    url::scheme_t scheme;
    std::string   host;
    uint16_t      port;
    std::string   path;
    std::string   query;
    std::string   fragment;
};

// Specify range because there are values not withing default range
template<>
struct enums::enum_range<url::scheme_t::enum_t>
{
    static constexpr auto min = 80;
    static constexpr auto max = 443;
};

} // namespace requests

#endif // REQUESTS_URL_HPP