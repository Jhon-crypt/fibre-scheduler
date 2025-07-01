add_executable(task1 task1.cpp)
target_link_libraries(task1 PRIVATE fibers)

add_executable(task2 task2.cpp)
target_link_libraries(task2 PRIVATE fibers)

add_executable(task3 task3.cpp)
target_link_libraries(task3 PRIVATE fibers) 