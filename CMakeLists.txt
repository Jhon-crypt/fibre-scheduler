cmake_minimum_required(VERSION 3.15)
project(fibre-scheduler VERSION 1.0.0 LANGUAGES CXX ASM)

# Set C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable testing
enable_testing()

# Add subdirectories
add_subdirectory(fibers)
add_subdirectory(my_string)
add_subdirectory(allocator)
add_subdirectory(tests)

# Set compiler flags
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif() 