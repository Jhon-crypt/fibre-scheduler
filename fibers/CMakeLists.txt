add_library(fibers INTERFACE)

target_include_directories(fibers
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Create test executable for context switching
add_executable(test_context
    test_context.cpp
)

target_link_libraries(test_context
    PRIVATE
        fibers
) 