cmake_minimum_required(VERSION 3.16)

# where to store lib at the build process
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# path to headers
set(
    requests_headers
        ${PROJECT_SOURCE_DIR}/include/requests/url.hpp
        ${PROJECT_SOURCE_DIR}/include/requests/method.hpp
        ${PROJECT_SOURCE_DIR}/include/requests/header.hpp
)

# path to sources
set(
    requests_sources
        url.cpp
        method.cpp
        header.cpp
)

add_library(requests ${requests_sources} ${requests_headers})
add_library(librequests::requests ALIAS requests)

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

# install library itself
install(
    TARGETS requests
    LIBRARY DESTINATION lib
)

# Also install the headers
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/requests DESTINATION include)