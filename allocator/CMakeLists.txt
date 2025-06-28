# Placeholder for allocator library
add_library(allocator INTERFACE)
add_executable(test_bump_allocator test_bump_allocator.cpp)
add_test(NAME test_bump_allocator COMMAND test_bump_allocator) 