# Placeholder for my_string library
add_library(my_string INTERFACE)
add_executable(test_my_string test_my_string.cpp)
add_test(NAME test_my_string COMMAND test_my_string) 