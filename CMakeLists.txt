cmake_minimum_required(VERSION 3.16)

# project info
project(
    librequests
        VERSION 0.0.0
        DESCRIPTION "C++ Requests library"
        HOMEPAGE_URL https://github.com/gavrilikhin-d/librequests
        LANGUAGES CXX
)

# Support folders in IDE's
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# add library code
add_subdirectory(src)

# tests
option(REQUESTS_BUILD_TESTS "Build test for LibRequest" OFF)

if(REQUESTS_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()