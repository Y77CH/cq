#ifndef REQUESTS_HEADER_HPP
#define REQUESTS_HEADER_HPP

#include <string>
#include <string_view>

namespace requests {

// Single HTTP header
class header
{
public:

    // Possible headers
    enum enum_t {
        authorization,
        host,
        user_agent
    };


    // Create header from its enum name and value
    header(const header::enum_t &name, std::string_view value)
    : m_name_enum(name), m_value(value) {}

    // Create header from its string name and value
    header(std::string_view name, std::string_view value);


    // Enum wrapper for header name
    class name_t
    {
    public:

        // Wrapp enum
        explicit name_t(const header::enum_t &e) : m_e(e) {}


        // Unwrapp enum using implicit cast
        operator header::enum_t() const noexcept { return m_e; }


        // Unwrapp enum
        [[nodiscard]] enum_t as_enum() const noexcept { return m_e; }

        // Get header name string representation
        [[nodiscard]] std::string as_string() const noexcept;

    private:
        header::enum_t m_e;
    };

    // Get wrapped header name
    [[nodiscard]] name_t name() const noexcept { return name_t(m_name_enum); }

    // Get header value
    [[nodiscard]] std::string value() const noexcept { return m_value; }


    // Get header string representation
    [[nodiscard]] std::string as_string() const noexcept { return name().as_string() + ": " + m_value; }

private:
    header::enum_t m_name_enum;
    std::string    m_value;
};

} // namespace requests

#endif // REQUESTS_HEADER_HPP