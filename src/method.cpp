#include "requests/method.hpp"

#include <array>

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


struct requests::method::impl
{
    method::enum_t e;
};


requests::method::method(const method::enum_t &e) : pimpl(new impl())
{
    pimpl->e = e;
}

requests::method::method(std::string_view v) : pimpl(new impl())
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
        pimpl->e = static_cast<method::enum_t>(std::distance(arr.begin(), it));
    }
    else
    {
        throw std::invalid_argument(
            std::string{v} + " is not a supported method!"
        );
    }
}


requests::method::~method() {}


requests::method::enum_t requests::method::as_enum() const noexcept { return pimpl->e; }

std::string requests::method::as_string() const noexcept { return std::string{arr.at(pimpl->e)}; }
