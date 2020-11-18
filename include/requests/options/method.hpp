#ifndef REQUESTS_OPTIONS_METHOD_HPP
#define REQUESTS_OPTIONS_METHOD_HPP

#include "requests/detail/enum.hpp"


namespace Requests {

namespace Detail {

// Inheritable enum class
struct Method_Helper
{
    // Possible methods (values are from boost)
    enum enum_t {
        DELETE  = 1,
        GET     = 2,
        HEAD    = 3,
        POST    = 4,
        PUT     = 5,
        OPTIONS = 7,
        PATCH   = 29
    };
};

template<>
struct Enum_Range<Method_Helper::enum_t>
{
    static constexpr auto min = 1;
    static constexpr auto max = 29;
};

} // namespace Detail


// Request method
struct Method
    : public Detail::Method_Helper,
      public Detail::Enum<Detail::Method_Helper::enum_t, Detail::Case_Insensitive>
{ using Detail::Enum<Detail::Method_Helper::enum_t, Detail::Case_Insensitive>::Enum; };

} // namespace Requests

#endif // REQUESTS_OPTIONS_METHOD_HPP