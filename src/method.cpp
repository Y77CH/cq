#include "requests/method.hpp"

#include <unordered_map>

struct requests::method::impl
{
    method::verbs verb;
};

requests::method::method(const verbs &v) : pimpl(new impl())
{
    pimpl->verb = v;
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

    // Map method string with verbs
    static const std::unordered_map<std::string_view, method::verbs> map = {
        { "DELETE",  verbs::DELETE  },
        { "GET",     verbs::GET     },
        { "HEAD",    verbs::HEAD    },
        { "OPTIONS", verbs::OPTIONS },
        { "PATCH",   verbs::PATCH   },
        { "POST",    verbs::POST    },
        { "PUT",     verbs::PUT     },
    };

    // Check if one of supported methods
    if (map.contains(str))
    {
        pimpl->verb = map.at(str);
    }
    else
    {
        throw std::invalid_argument(
            std::string{v} + " is not a supported method!"
        );
    }
}

requests::method::~method() {}

requests::method::verbs requests::method::verb() const noexcept { return pimpl->verb; }

std::string requests::method::str() const noexcept
{
    // Map verbs with method strings
    static const std::unordered_map<method::verbs, std::string_view> map = {
        { verbs::DELETE,  "DELETE"  },
        { verbs::GET,     "GET"     },
        { verbs::HEAD,    "HEAD"    },
        { verbs::OPTIONS, "OPTIONS" },
        { verbs::PATCH,   "PATCH"   },
        { verbs::POST,    "POST"    },
        { verbs::PUT,     "PUT"     }
    };

    return std::string{map.at(pimpl->verb)};
}
