cmake_minimum_required(VERSION 2.8)
project(cpp-snippets)
set(CMAKE_CXX_STANDARD 11)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/dep)

# Temporary disabled for link error under macOS
#add_executable(check_if_member_function_exists src/check_if_member_function_exists.cpp)
#target_link_libraries(check_if_member_function_exists ${GTEST_BOTH_LIBRARIES})

add_executable(function_template_partial_specialization src/function_template_partial_specialization.cpp)
target_link_libraries(function_template_partial_specialization ${GTEST_BOTH_LIBRARIES})

add_executable(virtual_function_call_benchmark src/virtual_function_call_benchmark.cpp)

add_executable(std_algorithm src/std_algorithm.cpp)
