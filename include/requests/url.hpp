#ifndef REQUESTS_URL_HPP
#define REQUESTS_URL_HPP

#include <string>
#include <string_view>

namespace requests {

// Uniform Resource Locators [RFC1738]
class url
{
public:

    // Possible url schemes
    enum class scheme_t : uint8_t {
        http,
        https
    };


    // Create URL from string
    explicit url(std::string_view url);


    /* Get methods */
    [[nodiscard]] scheme_t    scheme()   const noexcept { return m_scheme;   }
    [[nodiscard]] std::string host()     const noexcept { return m_host;     }
    [[nodiscard]] uint16_t    port()     const noexcept { return m_port;     }
    [[nodiscard]] std::string path()     const noexcept { return m_path;     }
    [[nodiscard]] std::string query()    const noexcept { return m_query;    }
    [[nodiscard]] std::string fragment() const noexcept { return m_fragment; }

    // Return URL string
    [[nodiscard]] std::string str() const noexcept;

private:
    url::scheme_t m_scheme;
    std::string   m_host;
    uint16_t      m_port;
    std::string   m_path;
    std::string   m_query;
    std::string   m_fragment;
};

} // namespace requests

#endif // REQUESTS_URL_HPP