cmake_minimum_required(VERSION 3.20)
project(Simple_Banking_Tests CXX)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(unit_tests
        bank_tests.cpp
        ../src/core/Account.cpp
        ../src/core/Bank.cpp
)

target_link_libraries(unit_tests PRIVATE gtest_main)
target_include_directories(unit_tests PRIVATE ../src/core)

include(GoogleTest)
gtest_discover_tests(unit_tests)