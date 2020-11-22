#ifndef REQUESTS_OPTIONS_DATA_HPP
#define REQUESTS_OPTIONS_DATA_HPP

#include <unordered_map>
#include <string>

namespace Requests {

struct Data : std::unordered_multimap<std::string, std::string>
{
    using std::unordered_multimap<std::string, std::string>::unordered_multimap;
};

} // namespace Requests

#endif // REQUESTS_OPTIONS_DATA_HPP