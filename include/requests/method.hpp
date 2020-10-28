#ifndef REQUESTS_METHOD_HPP
#define REQUESTS_METHOD_HPP

#include <string>
#include <string_view>

namespace requests {

// Request method
class method
{
public:

    // Possible methods
    enum enum_t : uint8_t {
        DELETE,
        GET,
        HEAD,
        OPTIONS,
        PATCH,
        POST,
        PUT
    };


    // Construct method from enum
    explicit method(const method::enum_t &e) : m_e(e) {}

    /**
     * @brief Create method from method string.
     *
     * @note: Throws exception if not found in enum
     */
    explicit method(std::string_view);


    // Get method enum entry
    [[nodiscard]] enum_t as_enum() const noexcept { return m_e; }

    // Get method string representation (all caps)
    [[nodiscard]] std::string as_string() const noexcept;

private:
    method::enum_t m_e;
};

} // namespace requests

#endif // REQUESTS_METHOD_HPP