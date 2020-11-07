#include "requests/header.hpp"


requests::header::header(
    const header::name_t &name,
    std::string_view value
) : name(name), value(value) {}

requests::header::header(
    std::string_view name,
    std::string_view value
) : name(name), value(value) {}

std::string requests::header::as_string() const noexcept
{
    return std::string{name.as_view()} + ": " + value;
}