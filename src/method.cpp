#include "requests/method.hpp"

#include <array>
#include <stdexcept>

// Map method string with enum
constexpr std::array<std::string_view, 7> arr = {
    "DELETE",
    "GET",
    "HEAD",
    "OPTIONS",
    "PATCH",
    "POST",
    "PUT"
};


requests::method::method(std::string_view v)
{
    // Method string
    std::string str {v};

    // Make it uppercase
    std::transform(
        str.begin(), str.end(),
        str.begin(), [](auto &&c){ return std::toupper(c); }
    );

    // Check if one of supported methods
    if (auto &&it = std::find(arr.begin(), arr.end(), str); it != arr.end())
    {
        m_e = static_cast<method::enum_t>(std::distance(arr.begin(), it));
    }
    else
    {
        throw std::invalid_argument(
            std::string{v} + " is not a supported method!"
        );
    }
}

std::string requests::method::as_string() const noexcept { return std::string{arr.at(m_e)}; }
