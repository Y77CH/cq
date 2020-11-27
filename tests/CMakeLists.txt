cmake_minimum_required(VERSION 3.16)

# where to store executable tests
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

option(USE_SYSTEM_GTEST "Use preinstalled googletest" ON)

# configure GTEST
if(USE_SYSTEM_GTEST)
    find_package(GTest)
endif()
if(NOT USE_SYSTEM_GTEST OR NOT GTEST_FOUND)
    # get dependencies from net
    include(FetchContent)

    message(STATUS "Not using system gtest, using built-in googletest project instead.")
    FetchContent_Declare(
        googletest
            URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz
            URL_HASH SHA256=9dc9157a9a1551ec7a7e43daea9a694a0bb5fb8bec81235d8a1e6ef64c716dcb
            USES_TERMINAL_DOWNLOAD TRUE)
    FetchContent_MakeAvailable(googletest)

    add_library(gtest_int INTERFACE)
    target_link_libraries(gtest_int INTERFACE gtest)
    target_include_directories(gtest_int INTERFACE ${googletest_SOURCE_DIR}/include)

    add_library(GTest::GTest ALIAS gtest_int)

    # Group under the "tests/gtest" project folder in IDEs such as Visual Studio.
    set_property(TARGET gtest PROPERTY FOLDER "tests/gtest")
    set_property(TARGET gtest_main PROPERTY FOLDER "tests/gtest")
endif()

# macro for easy tests adding
macro(add_requests_test _TEST_NAME)
    add_executable(${_TEST_NAME}_tests ${_TEST_NAME}_tests.cpp)
    target_link_libraries(
        ${_TEST_NAME}_tests
            PRIVATE
            requests
            GTest::GTest)
    add_test(NAME ${_TEST_NAME}_tests COMMAND ${_TEST_NAME}_tests)
    # Group under the "tests" project folder in IDEs such as Visual Studio.
    set_property(TARGET ${_TEST_NAME}_tests PROPERTY FOLDER "tests")
endmacro()

add_requests_test(method)
add_requests_test(requests)
add_requests_test(url)