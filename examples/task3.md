# Task 3: Fiber Scheduler Implementation

This example demonstrates the implementation of a basic fiber scheduler, showcasing how to manage multiple fibers and their execution contexts. It provides a foundation for understanding cooperative multitasking using fibers.

## Overview

The program implements a complete fiber scheduling system with:
1. A `fiber` class for managing individual fibers
2. A `scheduler` class for coordinating fiber execution
3. Function-to-fiber conversion
4. Round-robin scheduling of multiple fibers

## Technical Components

### Fiber Class
The `fiber` class encapsulates:
- Individual execution context
- Stack space management
- Function pointer storage
- Stack alignment and red zone compliance

### Scheduler Class
The scheduler provides:
- Fiber queue management
- Context switching between fibers
- Fiber spawning mechanism
- Clean exit handling

## Code Explanation

```cpp
#include "../fibers/context.hpp"
#include <iostream>
#include <deque>
#include <memory>

// Forward declarations
class fiber;
class scheduler;

// Global scheduler instance
scheduler* s = nullptr;

class fiber {
    friend class scheduler;
    Context context;
    char stack[4096];
    void (*func)();

public:
    fiber(void (*f)()) : func(f) {
        // Set up stack pointer
        char* sp = stack + sizeof(stack);
        
        // 16-byte alignment
        sp = reinterpret_cast<char*>(
            reinterpret_cast<uintptr_t>(sp) & ~0xFULL
        );
        
        // Red zone
        sp -= 128;
        
        // Initialize context (will be set up when first switched to)
        context = Context();
    }

    void start() {
        func();
    }
};

class scheduler {
    std::deque<fiber*> fibers_;
    Context context_;

public:
    scheduler() = default;
    ~scheduler() = default;

    void spawn(fiber* f) {
        fibers_.push_back(f);
    }

    void do_it() {
        // Save scheduler context to return here
        if (get_context(&context_) == 0) {
            if (!fibers_.empty()) {
                fiber* f = fibers_.front();
                fibers_.pop_front();
                f->start();
            }
        }
    }

    void fiber_exit() {
        // Return to scheduler loop
        set_context(&context_);
    }
};
```

### Key Components Detailed Analysis

#### 1. Fiber Class Design
```cpp
class fiber {
    friend class scheduler;
    Context context;
    char stack[4096];
    void (*func)();
    // ...
}
```
- Manages individual fiber state
- Contains dedicated stack space (4KB)
- Stores function pointer
- Handles stack alignment and setup
- Provides friend access to scheduler

#### 2. Stack Management
```cpp
char* sp = stack + sizeof(stack);
sp = reinterpret_cast<char*>(
    reinterpret_cast<uintptr_t>(sp) & ~0xFULL
);
sp -= 128;
```
- Allocates fixed-size stack (4KB)
- Ensures 16-byte alignment (System V ABI)
- Implements 128-byte red zone
- Sets up initial stack pointer

#### 3. Scheduler Implementation
```cpp
class scheduler {
    std::deque<fiber*> fibers_;
    Context context_;
    // ...
}
```
- Uses std::deque for fiber queue
- Maintains scheduler context
- Implements round-robin scheduling
- Handles fiber lifecycle

#### 4. Scheduling Operations
```cpp
void do_it() {
    if (get_context(&context_) == 0) {
        if (!fibers_.empty()) {
            fiber* f = fibers_.front();
            fibers_.pop_front();
            f->start();
        }
    }
}
```
- Saves scheduler context
- Retrieves next fiber
- Initiates fiber execution
- Handles empty queue case

### Example Usage

```cpp
void func1() {
    std::cout << "fiber 1 before" << std::endl;
    std::cout << "fiber 1 after" << std::endl;
    s->fiber_exit();
}

void func2() {
    std::cout << "fiber 2" << std::endl;
    s->fiber_exit();
}

int main() {
    s = new scheduler();
    
    fiber* f2 = new fiber(func2);
    fiber* f1 = new fiber(func1);
    
    s->spawn(f1);
    s->spawn(f2);
    
    s->do_it();
    s->do_it();
    
    delete f1;
    delete f2;
    delete s;
    
    return 0;
}
```

## Program Flow

1. **Initialization**:
   - Scheduler creation
   - Fiber creation with functions
   - Fiber registration with scheduler

2. **Execution**:
   - Scheduler saves its context
   - First fiber executes
   - Fiber exits back to scheduler
   - Next fiber is scheduled
   - Process repeats

3. **Cleanup**:
   - Resources are freed
   - Memory is deallocated

## Expected Output

```
fiber 1 before
fiber 1 after
fiber 2
```

### Output Analysis:
- First two lines: Complete execution of first fiber
- Third line: Execution of second fiber
- Order demonstrates successful scheduling

## Memory Management

### Stack Layout Per Fiber
```
High Address
+------------------+
|   Fiber Stack    |
|    (4096 bytes)  |
|                  |
+------------------+
|   128-byte       |
|   Red Zone       |
+------------------+
Low Address
```

### Heap Allocations
- Scheduler instance
- Fiber instances
- Fiber management queue

## Building and Running

### Prerequisites
- CMake (3.10 or higher)
- C++ compiler with C++11 support
- x86_64 architecture

### Build Steps
```bash
# From the project root directory
mkdir build           # Create build directory
cd build             # Enter build directory
cmake ..             # Generate build files
make                 # Build the project
```

### Running the Example
```bash
./examples/task3
```

## Debugging Tips

### GDB Commands
```bash
gdb ./examples/task3
```

Useful debugging commands:
- `break fiber::start` - Break at fiber execution
- `break scheduler::do_it` - Break at scheduling points
- `p fibers_` - Examine fiber queue
- `bt` - Check call stack during fiber execution

## Performance Considerations

1. **Memory Usage**:
   - Fixed stack size per fiber (4KB)
   - Queue memory overhead
   - Context structure size

2. **Context Switching**:
   - Stack setup cost
   - Queue operations overhead
   - Register state management

3. **Scheduling Efficiency**:
   - Round-robin simplicity
   - FIFO queue performance
   - No priority handling

## Common Pitfalls

1. **Resource Management**:
   - Memory leaks from undeleted fibers
   - Dangling fiber pointers
   - Stack overflow in fiber functions

2. **Scheduling Issues**:
   - Infinite loops in fibers
   - Missing fiber_exit() calls
   - Queue management errors

3. **Stack Problems**:
   - Insufficient stack space
   - Stack alignment violations
   - Red zone corruption

## Best Practices

1. **Resource Handling**:
   - Use smart pointers for fiber management
   - Implement proper cleanup in destructors
   - Check for memory leaks

2. **Error Handling**:
   - Validate fiber creation
   - Check queue operations
   - Handle empty scheduler case

3. **Stack Usage**:
   - Monitor stack consumption
   - Maintain proper alignment
   - Respect red zone boundaries 