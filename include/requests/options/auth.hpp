#ifndef REQUESTS_OPTIONS_AUTH_HPP
#define REQUESTS_OPTIONS_AUTH_HPP

#include <string>


namespace Requests {

// Basic authorization
struct Auth
{
    std::string username;
    std::string password;


    // Get authorization string base64 encoded
    std::string to_base64() const noexcept;
};

} // namespace Requests

#endif // REQUESTS_OPTIONS_DATA_HPP