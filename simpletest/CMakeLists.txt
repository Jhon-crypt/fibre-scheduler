cmake_minimum_required(VERSION 3.10)
project(simpletest)

# Create header-only library
add_library(simpletest INTERFACE)
target_include_directories(simpletest INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}) 