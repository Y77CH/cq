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
    // Possible method verbs
    enum class verbs {
        DELETE,
        GET,
        HEAD,
        OPTIONS,
        PATCH,
        POST,
        PUT
    };


    // Construct method from enum
    explicit method(const verbs &);

    /**
     * @brief Create method from verb string.
     *
     * @note: Throws exception if now found in enum
     */
    explicit method(std::string_view);

    // Destructor for pimpl
    ~method();


    // Get method enum entry
    [[nodiscard]] verbs verb() const noexcept;

    // Get method string representation (all caps)
    [[nodiscard]] std::string str() const noexcept;

private:
    struct impl;
    std::unique_ptr<impl> pimpl;
};

} // namespace requests

#endif // REQUESTS_METHOD_HPP