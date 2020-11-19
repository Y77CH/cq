#ifndef REQUESTS_OPTIONS_URL_HPP
#define REQUESTS_OPTIONS_URL_HPP

#include <string>
#include <string_view>

#include "requests/detail/enum.hpp"

#include "requests/options/fragment.hpp"
#include "requests/options/query.hpp"


namespace Requests {

class Url
{
private:
    // Inheritable enum class
    struct Scheme_Helper {
        // Possible schemes
        enum enum_t {
            http  = 80,
            https = 443
        };
    };

public:
    // Scheme enum wrapper
    struct Scheme
        : public Scheme_Helper,
          public Detail::Enum<Scheme_Helper::enum_t, Detail::Case_Insensitive>
    { using Detail::Enum<Scheme_Helper::enum_t, Detail::Case_Insensitive>::Enum; };


    Scheme      scheme;
    std::string host;
    uint16_t    port;
    std::string path;
    std::string query;
    std::string fragment;


    // Create URL from string
    Url(std::string_view url);

    // Create URL from string
    Url(const char *url) : Url(std::string_view{url}) {}


    // Return URL string
    [[nodiscard]] std::string to_string() const noexcept;
};


// Make all enum values be in range
template<>
struct Detail::Enum_Range<Url::Scheme::enum_t>
{
    static constexpr auto min = 80;
    static constexpr auto max = 443;
};

} // namespace Requests

#endif // REQUESTS_OPTIONS_URL_HPP