#ifndef REQUESTS_OPTIONS_HEADERS_HPP
#define REQUESTS_OPTIONS_HEADERS_HPP

#include <string>
#include <string_view>
#include <unordered_map>


namespace Requests {

inline namespace Comparators {

struct Case_Insensitive
{
    bool operator()(std::string_view, std::string_view) const noexcept;
};

} // namespace Comparators


// Single HTTP header
struct Header
{
    std::string name;
    std::string value;
};


// Collection of HTTP headers
struct Headers : std::unordered_map<std::string, std::string, std::hash<std::string>, Case_Insensitive>
{
    using std::unordered_map<
        std::string, std::string,
        std::hash<std::string>,
        Case_Insensitive
    >::unordered_map;
};

} // namespace Requests

#endif // REQUESTS_OPTIONS_HEADERS_HPP