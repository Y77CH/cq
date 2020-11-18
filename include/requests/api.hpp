#ifndef REQUESTS_API_HPP
#define REQUESTS_API_HPP

#include "requests/options/url.hpp"
#include "requests/response.hpp"


namespace Requests {

/**
 * @brief Construct and send a DELETE Request
 *
 * @tparam Args Request options
 * @param url Request URL
 * @param args List of the Request options
 * @return Response
 */
template<typename ...Args>
Response delet(const Url &url, const Args & ...args);


/**
 * @brief Construct and send a GET Request
 *
 * @tparam Args Request options
 * @param url Request URL
 * @param args List of the Request options
 * @return Response
 */
template<typename ...Args>
Response get(const Url &url, const Args & ...args);


/**
 * @brief Construct and send a HEAD Request
 *
 * @tparam Args Request options
 * @param url Request URL
 * @param args List of the Request options
 * @return Response
 */
template<typename ...Args>
Response head(const Url &url, const Args & ...args);


/**
 * @brief Construct and send a OPTIONS Request
 *
 * @tparam Args Request options
 * @param url Request URL
 * @param args List of the Request options
 * @return Response
 */
template<typename ...Args>
Response options(const Url &url, const Args & ...args);


/**
 * @brief Construct and send a PATCH Request
 *
 * @tparam Args Request options
 * @param url Request URL
 * @param args List of the Request options
 * @return Response
 */
template<typename ...Args>
Response patch(const Url &url, const Args & ...args);


/**
 * @brief Construct and send a POST Request
 *
 * @tparam Args Request options
 * @param url Request URL
 * @param args List of the Request options
 * @return Response
 */
template<typename ...Args>
Response post(const Url &url, const Args & ...args);


/**
 * @brief Construct and send a PUT Request
 *
 * @tparam Args Request options
 * @param url Request URL
 * @param args List of the Request options
 * @return Response
 */
template<typename ...Args>
Response put(const Url &url, const Args & ...args);

} // namespace Requests

#include "requests/impl/api.ipp"

#endif // REQUESTS_API_HPP