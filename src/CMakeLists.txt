cmake_minimum_required(VERSION 3.16)

# where to store lib at the build process
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# path to headers
set(
    requests_headers
        ${PROJECT_SOURCE_DIR}/include/requests/api.hpp
        ${PROJECT_SOURCE_DIR}/include/requests/detail/enum.hpp
        ${PROJECT_SOURCE_DIR}/include/requests/impl/api.ipp
        ${PROJECT_SOURCE_DIR}/include/requests/impl/session.ipp
        ${PROJECT_SOURCE_DIR}/include/requests/options/fragment.hpp
        ${PROJECT_SOURCE_DIR}/include/requests/options/headers.hpp
        ${PROJECT_SOURCE_DIR}/include/requests/options/method.hpp
        ${PROJECT_SOURCE_DIR}/include/requests/options/query.hpp
        ${PROJECT_SOURCE_DIR}/include/requests/options/url.hpp
        ${PROJECT_SOURCE_DIR}/include/requests/options.hpp
        ${PROJECT_SOURCE_DIR}/include/requests/request.hpp
        ${PROJECT_SOURCE_DIR}/include/requests/requests.hpp
        ${PROJECT_SOURCE_DIR}/include/requests/response.hpp
        ${PROJECT_SOURCE_DIR}/include/requests/session.hpp
)

# path to sources
set(
    requests_sources
        session.cpp
        url.cpp
)

add_library(requests ${requests_sources} ${requests_headers})

# Specify directories which the compiler should look for headers
target_include_directories(
    requests
        PRIVATE ${PROJECT_SOURCE_DIR}/src
        PUBLIC  ${PROJECT_SOURCE_DIR}/include
)

# IDEs should put the headers in a nice place
source_group(
    TREE "${PROJECT_SOURCE_DIR}/include"
    PREFIX "Header Files"
    FILES ${HEADER_LIST}
)

# All users of this library will need at least C++20
target_compile_features(requests PUBLIC cxx_std_20)

# configure OpenSSL
find_package(OpenSSL COMPONENTS Crypto SSL)
target_link_libraries(requests OpenSSL::SSL OpenSSL::Crypto)

# configure Boost
find_package(Boost 1.66)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(requests Boost::boost)

# install library itself
install(
    TARGETS requests
    LIBRARY DESTINATION lib
)

# Also install the headers
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/requests DESTINATION include)