#ifndef REQUESTS_OPTIONS_TEXT_HPP
#define REQUESTS_OPTIONS_TEXT_HPP

#include <string>

namespace Requests {

struct Text : std::string
{
    using std::string::string;
};

} // namespace Requests

#endif // REQUESTS_OPTIONS_TEXT_HPP