#ifndef REQUESTS_METHOD_HPP
#define REQUESTS_METHOD_HPP

#include <memory>
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
    explicit method(const method::enum_t &);

    /**
     * @brief Create method from method string.
     *
     * @note: Throws exception if not found in enum
     */
    explicit method(std::string_view);


    // Destructor for pimpl
    ~method();


    // Get method enum entry
    [[nodiscard]] enum_t as_enum() const noexcept;

    // Get method string representation (all caps)
    [[nodiscard]] std::string as_string() const noexcept;

private:
    struct impl;
    std::unique_ptr<impl> pimpl;
};

} // namespace requests

#endif // REQUESTS_METHOD_HPP