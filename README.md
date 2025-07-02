# Fiber Scheduler Implementation

## Table of contents:

- [Task 1](#task-1)
  - [Overview](#task-1-overview)
  - [Main Implementation](#task-1-main-implementation)
  - [Output & Observations](#task-1-output--observations)
- [Task 2](#task-2)
  - [Overview](#task-2-overview)
  - [Implementation](#task-2-implementation)
  - [Output & Observations](#task-2-output--observations)
- [Task 3](#task-3)
  - [Overview](#task-3-overview)
  - [Implementation](#task-3-implementation)
  - [Output & Observations](#task-3-output--observations)

## Project Overview

This project aims to implement a fiber scheduler using cooperative multitasking with custom context management. Fibers, lightweight cooperative threads, are scheduled and executed in a non-preemptive manner. This README provides an overview of the code structure and highlights key features in the implementation that contributes to the functionality of the program.

## Task 1

### Task 1 Overview

Task 1 implements a basic context switching mechanism using the `Context` library. It demonstrates the fundamental concepts of saving and restoring execution contexts.

### Main Implementation

#### Data Structures
- **Context Object**: A `Context` object is used to store the program state
- **State Variable**: A volatile counter to control context switches

#### Functions
```cpp
int main() {
    Context ctx;
    volatile int x = 0;  // Mark as volatile to prevent optimization
    
    if (get_context(&ctx) == 0) {
        x++;
        if (x < 2) {
            std::cout << "a message" << std::endl;
            set_context(&ctx);
        }
    }
    std::cout << "a message" << std::endl;
    return 0;
}
```

#### Key Features
- Basic context saving and restoration
- State preservation between switches
- Proper optimization control
- Simple control flow demonstration

### Output & Observations
```
a message
a message
```
The output shows successful context switching with state preservation.

## Task 2

### Overview

Task 2 extends the context switching mechanism by implementing custom stack management and function execution contexts.

### Implementation

#### Key Components
```cpp
// Stack setup and management
char data[4096];
char* sp = data + 4096;

// System V ABI compliance
sp = reinterpret_cast<char*>(
    reinterpret_cast<uintptr_t>(sp) & ~0xFULL
);
sp -= 128;  // Red zone
```

#### Technical Features
- 4KB stack allocation
- 16-byte stack alignment
- 128-byte red zone
- Function context creation

### Output & Observations
```
you called foo
Back in main
```
Demonstrates successful function execution with custom stack management.

## Task 3

### Overview

Task 3 implements a complete fiber scheduler that manages multiple fibers and their execution contexts.

### Implementation

#### Fiber Class
```cpp
class fiber {
    Context context;
    char stack[4096];
    void (*func)();
public:
    fiber(void (*f)());
    void start();
};
```

#### Scheduler Class
```cpp
class scheduler {
    std::deque<fiber*> fibers_;
    Context context_;
public:
    void spawn(fiber* f);
    void do_it();
    void fiber_exit();
};
```

#### Key Features
- Fiber management
- Round-robin scheduling
- Resource handling
- Context switching control

### Output & Observations
```
fiber 1 before
fiber 1 after
fiber 2
```
Shows successful fiber scheduling and execution.

## Building and Running

### Prerequisites
- CMake (3.10 or higher)
- C++ compiler with C++11 support
- x86_64 architecture

### Build Steps
```bash
mkdir build
cd build
cmake ..
make
```

### Running Examples
```bash
./examples/task1  # Basic context switching
./examples/task2  # Stack management
./examples/task3  # Fiber scheduler
```

## Project Structure
```
fibre-scheduler/
  ├── allocator/
  │   ├── bump_allocator.hpp
  │   ├── CMakeLists.txt
  │   └── test_bump_allocator.cpp
  ├── examples/
  │   ├── task1.cpp
  │   ├── task2.cpp
  │   └── task3.cpp
  ├── fibers/
  │   ├── context.hpp
  │   └── test_context.cpp
  └── CMakeLists.txt
```

## Contributing

When modifying or extending this project:
1. Ensure proper context management
2. Maintain stack alignment requirements
3. Follow System V ABI specifications
4. Add appropriate test cases
5. Document any platform-specific considerations 