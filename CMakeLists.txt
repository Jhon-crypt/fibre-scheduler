cmake_minimum_required(VERSION 3.15)
project(fibre-scheduler CXX)

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