#include "requests/options/headers.hpp"

bool Requests::Comparators::Case_Insensitive::operator()(
    std::string_view lhs, std::string_view rhs
) const noexcept
{
    if (lhs.size() != rhs.size()) { return false; }

    for (size_t i = 0; i < lhs.size(); ++i)
    {
        if (std::tolower(lhs[i]) != std::tolower(rhs[i])) { return false; }
    }

    return true;
}