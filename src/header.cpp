#include "requests/header.hpp"

#include <array>
#include <stdexcept>

// Map header name string with enum
constexpr std::array<std::string_view, 3> arr = {
    "authorization",
    "host",
    "user-agent"
};


requests::header::name_t::name_t(std::string_view name)
{
    // Header name string
    std::string str {name};

    // Make it lowercase
    std::transform(
        str.begin(), str.end(),
        str.begin(), [](auto &&c){ return std::tolower(c); }
    );

    // Check if one of supported names
    if (auto &&it = std::find(arr.begin(), arr.end(), str); it != arr.end())
    {
        m_e = static_cast<header::enum_t>(std::distance(arr.begin(), it));
    }
    else
    {
        throw std::invalid_argument(
            std::string{name} + " is not a supported header name!"
        );
    }
}


std::string requests::header::name_t::as_string() const noexcept
{
    return std::string{arr.at(m_e)};
}