#ifndef REQUESTS_URL_HPP
#define REQUESTS_URL_HPP

#include <memory>
#include <string>
#include <string_view>

namespace requests {

// Uniform Resource Locators [RFC1738]
class url
{
public:
    // Possible url schemes
    enum class schemes : uint8_t {
        none = 0,
        http,
        https
    };

    // Allow empty URLs
    url();

    // Create URL from string
    explicit url(std::string_view url);

    // Destructor for pimpl;
    ~url();

    /* Get methods */
    [[nodiscard]] schemes     scheme()   const noexcept;
    [[nodiscard]] std::string host()     const noexcept;
    [[nodiscard]] uint16_t    port()     const noexcept;
    [[nodiscard]] std::string path()     const noexcept;
    [[nodiscard]] std::string query()    const noexcept;
    [[nodiscard]] std::string fragment() const noexcept;

    // Return URL string
    [[nodiscard]] std::string str() const noexcept;

private:
    struct impl;
    std::unique_ptr<impl> pimpl;
};

} // namespace requests

#endif // REQUESTS_URL_HPP