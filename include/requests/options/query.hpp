#ifndef REQUESTS_OPTIONS_QUERY_HPP
#define REQUESTS_OPTIONS_QUERY_HPP

#include <string>
#include <unordered_map>


namespace Requests {

struct Query : std::unordered_multimap<std::string, std::string>
{
    using std::unordered_multimap<std::string, std::string>::unordered_multimap;
};

} // namespace Requests

#endif // REQUESTS_OPTIONS_QUERY_HPP