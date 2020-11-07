#ifndef REQUESTS_METHOD_HPP
#define REQUESTS_METHOD_HPP

#include "requests/enums.hpp"

namespace requests {

namespace detail {

// Inheritable enum class
struct method_helper
{
    // Possible methods
    enum enum_t {
        DELETE,
        GET,
        HEAD,
        OPTIONS,
        PATCH,
        POST,
        PUT
    };
};

} // namespace detail

// Specify range for compiler to do less work
template<>
struct enums::enum_range<detail::method_helper::enum_t>
{
    static constexpr auto min = 0;
    static constexpr auto max = 6;
};

// Request method
struct method : public detail::method_helper,
                public enums::enum_wrapper<detail::method_helper::enum_t, enums::case_insensitive>
{ using enums::enum_wrapper<detail::method_helper::enum_t, enums::case_insensitive>::enum_wrapper; };

}; // namespace requests

#endif // REQUESTS_METHOD_HPP