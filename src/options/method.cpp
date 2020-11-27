#include "requests/options/method.hpp"

#include <array>
#include <stdexcept>


constexpr std::array enum_to_str_mapper = {
    std::pair{ Requests::Method::DELETE,  "DELETE"  },
    std::pair{ Requests::Method::GET,     "GET"     },
    std::pair{ Requests::Method::HEAD,    "HEAD"    },
    std::pair{ Requests::Method::POST,    "POST"    },
    std::pair{ Requests::Method::PUT,     "PUT"     },
    std::pair{ Requests::Method::OPTIONS, "OPTIONS" },
    std::pair{ Requests::Method::PATCH,   "PATCH"   }
};

constexpr bool case_insensitive_eq(std::string_view lhs, std::string_view rhs) noexcept
{
    if (lhs.size() != rhs.size()) { return false; }

    for (size_t i = 0; i < lhs.size(); ++i)
    {
        if (std::tolower(lhs[i]) != std::tolower(rhs[i])) { return false; }
    }

    return true;
}


// Construct method from string. Case-insensitive
Requests::Method::Method(std::string_view str)
{
    bool found = false;
    for (const auto &[e, name] : enum_to_str_mapper)
    {
        if (case_insensitive_eq(str, name))
        {
            m_e = e;
            found = true;
            break;
        }
    }

    if (!found) { throw std::invalid_argument("Invalid method!"); }
}


// Return Method string all caps
std::string Requests::Method::to_string() const noexcept
{
    for (const auto &[e, name] : enum_to_str_mapper)
    {
        if (m_e == e) { return name; }
    }

    return "";
}
