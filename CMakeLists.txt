cmake_minimum_required(VERSION 3.10)
project(worksheet2)

# Set C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable testing
enable_testing()

# Add subdirectories
add_subdirectory(fibers)
add_subdirectory(my_string)
add_subdirectory(allocator)
add_subdirectory(tests)
add_subdirectory(examples)

# Set compiler flags
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Task 1 - Basic bump allocator test
add_executable(task1_test task1_test.cpp)
target_include_directories(task1_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Task 3 - Benchmarking
add_executable(task3 task3.cpp)
target_include_directories(task3 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}) 