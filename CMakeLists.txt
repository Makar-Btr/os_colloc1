cmake_minimum_required(VERSION 3.14)
project(os_colloc1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_policy(SET CMP0135 NEW)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(
    runTests
    test/tests.cpp 
)

target_include_directories(
    runTests 
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/project
)

target_link_libraries(
    runTests
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(runTests)