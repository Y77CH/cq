#ifndef REQUESTS_OPTIONS_METHOD_HPP
#define REQUESTS_OPTIONS_METHOD_HPP

#include <string>
#include <string_view>


namespace Requests {

// Request method
class Method
{
public:
    // Possible methods. Values from Beast.
    enum enum_t {
        DELETE  = 1,
        GET     = 2,
        HEAD    = 3,
        POST    = 4,
        PUT     = 5,
        OPTIONS = 7,
        PATCH   = 29
    };


    Method() = default;

    // Construct method from string. Case-insensitive
    Method(const char *str) : Method(std::string_view{str}) {}

    // Construct method from string. Case-insensitive
    Method(std::string_view);

    constexpr Method(enum_t e) noexcept : m_e(e) {}


    // Return Method string all caps
    std::string to_string() const noexcept;



    constexpr enum_t to_enum() const noexcept { return m_e; }


    constexpr operator enum_t&() noexcept { return m_e; }

    constexpr operator const enum_t&() const noexcept { return m_e; }

private:
    enum_t m_e;
};

} // namespace Requests

#endif // REQUESTS_OPTIONS_METHOD_HPP