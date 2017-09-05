cmake_minimum_required(VERSION 2.8)
project(cpp-snippets)
set(CMAKE_CXX_STANDARD 11)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(check_if_member_function_exists src/check_if_member_function_exists.cpp)
target_link_libraries(check_if_member_function_exists ${GTEST_BOTH_LIBRARIES})

