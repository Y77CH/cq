#ifndef REQUESTS_HEADER_HPP
#define REQUESTS_HEADER_HPP

#include <string>
#include <string_view>

#include "requests/enums.hpp"

namespace requests {

// Single HTTP header
struct header
{
private:
    // Case insensitive (also '-' == '_') comparator for header names
    struct name_equal
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

public:

    // Possible headers
    enum enum_t {
        authorization,
        host,
        user_agent
    };

    // Enum wrapper for header name
    class name_t : public enums::enum_wrapper<header::enum_t, name_equal>
    { using enums::enum_wrapper<header::enum_t, name_equal>::enum_wrapper; };


    // Create header from its enum name wrapper and value
    header(const header::name_t &name, std::string_view value);

    // Create header from its string name and value
    header(std::string_view name, std::string_view value);


    // Get header string representation
    [[nodiscard]] std::string as_string() const noexcept;

    header::name_t  name;
    std::string    value;
};

// Specify range for compiler to do less work
template<>
struct enums::enum_range<header::enum_t>
{
    static constexpr auto min = 0;
    static constexpr auto max = 2;
};

} // namespace requests

#endif // REQUESTS_HEADER_HPP