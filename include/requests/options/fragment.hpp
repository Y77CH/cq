#ifndef REQUESTS_OPTIONS_FRAGMENT_HPP
#define REQUESTS_OPTIONS_FRAGMENT_HPP

#include <string>


namespace Requests {

struct Fragment : std::string
{
    using std::string::string;
};

} // namespace Requests

#endif // REQUESTS_OPTIONS_FRAGMENT_HPP