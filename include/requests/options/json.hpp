#ifndef REQUESTS_OPTIONS_JSON_HPP
#define REQUESTS_OPTIONS_JSON_HPP

#include <string>

namespace Requests {

struct Json : std::string
{
    using std::string::string;
};

} // namespace Requests

#endif // REQUESTS_OPTIONS_JSON_HPP