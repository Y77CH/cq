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

    // Enum wrapper for header name
    class name_t
    {
    public:

        // Wrapp enum
        name_t(const header::enum_t &e) : m_e(e) {}

        // Make enum entry from string and wrapp it
        name_t(std::string_view);


        // Unwrapp enum using implicit cast
        operator header::enum_t() const noexcept { return m_e; }


        // Unwrapp enum
        [[nodiscard]] enum_t as_enum() const noexcept { return m_e; }

        // Get header name string representation
        [[nodiscard]] std::string as_string() const noexcept;

    private:
        header::enum_t m_e;
    };


    // Header field-value
    using value_t = std::string;


    // Create header from its enum name wrapper and value
    header(const header::name_t &name, std::string_view value)
    : m_name(name), m_value(value) {}

    // Create header from its enum name and value
    header(const header::enum_t &name, std::string_view value)
    : m_name(name), m_value(value) {}

    // Create header from its string name and value
    header(std::string_view name, std::string_view value)
    : m_name(name), m_value(value) {}


    // Get wrapped header name
    [[nodiscard]] name_t name() const noexcept { return m_name; }

    // Get header value
    [[nodiscard]] value_t value() const noexcept { return m_value; }

    // Set header value
    void value(std::string_view v) noexcept { m_value = v; }


    // Get header string representation
    [[nodiscard]] std::string as_string() const noexcept { return m_name.as_string() + ": " + m_value; }

private:
    header::name_t  m_name;
    header::value_t m_value;
};

} // namespace requests

#endif // REQUESTS_HEADER_HPP