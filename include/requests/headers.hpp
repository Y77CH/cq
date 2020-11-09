#ifndef REQUESTS_HEADERS_HPP
#define REQUESTS_HEADERS_HPP

#include <string>
#include <string_view>
#include <unordered_map>

#include "requests/enums.hpp"

namespace requests {

namespace detail {
    // Inheritable enum class
    struct header_helper
    {
        // Possible headers
        enum enum_t {
            authorization,
            host,
            user_agent
        };
    };

    // Case insensitive (also '-' == '_') comparator for header names
    struct header_name_equal
    {
        constexpr bool operator()(std::string_view lhs, std::string_view rhs) const noexcept
        {
            if (lhs.size() != rhs.size()) { return false; }

            for (size_t i = 0; i < lhs.size(); ++i)
            {
                auto c1 = ('A' <= lhs[i] && lhs[i] <= 'Z') ? (lhs[i] - 'A' + 'a') : lhs[i];
                auto c2 = ('A' <= rhs[i] && rhs[i] <= 'Z') ? (rhs[i] - 'A' + 'a') : rhs[i];

                if (c1 == '_') { c1 = '-'; }
                if (c2 == '_') { c2 = '-'; }

                if (c1 != c2) { return false; }
            }

            return true;
        }
    };

} // namespace detail


// Specify range for compiler to do less work
template<>
struct enums::enum_range<detail::header_helper::enum_t>
{
    static constexpr auto min = 0;
    static constexpr auto max = 2;
};



// Enum wrapper for header name
struct header : public detail::header_helper,
                public enums::enum_wrapper<detail::header_helper::enum_t, detail::header_name_equal>
{
    using enums::enum_wrapper<detail::header_helper::enum_t, detail::header_name_equal>::enum_wrapper;

    [[
        nodiscard,
        deprecated(
            "header::as_view() doesn't change '_' to '-'. "
            "Use header::as_string() instead!"
        )
    ]]
    constexpr std::string_view as_view() const { return enum_wrapper::as_view(); }

    // Get header name with '_' replaced by '-'
    [[nodiscard]] std::string as_string() const
    {
        std::string v {enum_wrapper::as_view()};

        std::transform(
            v.begin(), v.end(),
            v.begin(), [](char c){ return (c == '_') ? '-' : c; }
        );

        return v;
    }
};

// Collection of HTTP headers
using headers = std::unordered_map<header, std::string, std::hash<int>>;

} // namespace requests

#endif // REQUESTS_HEADERS_HPP