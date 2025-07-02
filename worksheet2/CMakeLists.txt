cmake_minimum_required(VERSION 3.10)
project(worksheet2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add simpletest
add_subdirectory(simpletest)

# Task 1 - Basic bump allocator test
add_executable(task1_test task1_test.cpp)
target_include_directories(task1_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Task 2 - Unit tests with simpletest
add_executable(task2 task2.cpp)
target_include_directories(task2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(task2 PRIVATE simpletest)

# Task 3 - Benchmarking
add_executable(task3 task3.cpp)
target_include_directories(task3 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}) 