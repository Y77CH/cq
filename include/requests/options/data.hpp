#ifndef REQUESTS_OPTIONS_DATA_HPP
#define REQUESTS_OPTIONS_DATA_HPP

#include <string>
#include <unordered_map>


namespace Requests {

struct Data : std::unordered_multimap<std::string, std::string>
{
    using std::unordered_multimap<std::string, std::string>::unordered_multimap;
};

} // namespace Requests

#endif // REQUESTS_OPTIONS_DATA_HPP