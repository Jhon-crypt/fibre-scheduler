# Task 2: Advanced Context Switching with Stack Manipulation

This example demonstrates advanced context switching techniques with manual stack management and function context creation. It shows how to create a new execution context for a function with its own stack space.

## Overview

The program implements a more sophisticated context switching scenario that:
1. Creates and manages multiple contexts (main and function contexts)
2. Allocates and configures custom stack space
3. Implements proper stack alignment following System V ABI
4. Demonstrates function execution with custom stack contexts

## Technical Background

### Stack Management

The example handles several critical aspects of stack management:
- Manual stack space allocation
- Proper stack alignment (16-byte alignment per System V ABI)
- Red zone implementation (128-byte protected region)
- Stack pointer manipulation

### System V ABI Compliance

The code follows the System V ABI requirements:
1. 16-byte stack alignment
2. 128-byte red zone below the stack pointer
3. Proper register state preservation

## Code Explanation

```cpp
#include "../fibers/context.hpp"
#include <iostream>
#include <cstdlib>
#include <cstdint>

Context main_ctx;
Context foo_ctx;

void foo() {
    std::cout << "you called foo" << std::endl;
    set_context(&main_ctx);
}

int main() {
    // Save main's context
    if (get_context(&main_ctx) == 0) {
        // Allocate space for stack (4096 bytes)
        char data[4096];
        
        // Stack pointer setup
        char* sp = data + 4096;
        
        // System V ABI: 16-byte stack alignment
        sp = reinterpret_cast<char*>(
            reinterpret_cast<uintptr_t>(sp) & ~0xFULL
        );
        
        // System V ABI: 128-byte red zone
        sp -= 128;
        
        // Create context for foo
        foo_ctx = main_ctx;  // Copy main's context as base
        foo_ctx.rsp = sp;    // Set new stack pointer
        
        // Switch to foo's context
        foo();
    }
    
    std::cout << "Back in main" << std::endl;
    return 0;
}
```

### Key Components Detailed Analysis:

#### 1. Context Objects
```cpp
Context main_ctx;
Context foo_ctx;
```
- `main_ctx`: Stores the main function's execution context
- `foo_ctx`: Stores the context for the `foo` function
- Both contexts are global to ensure accessibility

#### 2. Target Function
```cpp
void foo() {
    std::cout << "you called foo" << std::endl;
    set_context(&main_ctx);
}
```
- Simple function to demonstrate context switching
- Prints a message and returns to main's context
- Uses `set_context` to switch back to main

#### 3. Stack Allocation and Setup
```cpp
char data[4096];
char* sp = data + 4096;
```
- Allocates 4KB of stack space
- Sets stack pointer to the top of the allocated space
- Stack grows downward in x86_64 architecture

#### 4. Stack Alignment
```cpp
sp = reinterpret_cast<char*>(
    reinterpret_cast<uintptr_t>(sp) & ~0xFULL
);
```
- Ensures 16-byte stack alignment required by System V ABI
- Uses bitwise operations to align the stack pointer
- Critical for SSE/AVX instructions and function calls

#### 5. Red Zone Implementation
```cpp
sp -= 128;
```
- Implements the 128-byte red zone specified by System V ABI
- Provides scratch space for leaf functions
- Protects against stack overflow

#### 6. Context Setup
```cpp
foo_ctx = main_ctx;  // Copy main's context as base
foo_ctx.rsp = sp;    // Set new stack pointer
```
- Copies main's context as a starting point
- Updates stack pointer to use new stack space
- Preserves other register states

### Program Flow Detailed Breakdown:

1. **Initial Setup**:
   - Main context is saved
   - Stack space is allocated
   - Stack pointer is configured

2. **Context Preparation**:
   - Stack is aligned
   - Red zone is established
   - New context is created for `foo`

3. **Context Switch**:
   - Program switches to `foo`'s context
   - `foo` executes with new stack
   - Control returns to main

4. **Completion**:
   - Final message printed in main
   - Program terminates

## Expected Output

```
you called foo
Back in main
```

### Output Analysis:
- First line: Confirms successful execution in foo's context
- Second line: Confirms successful return to main's context

## Memory Layout

```
High Address
+------------------+
|                  |
|   Main's Stack   |
|                  |
+------------------+
|                  |
|   Foo's Stack    |
|    (4096 bytes)  |
|                  |
+------------------+
|   128-byte       |
|   Red Zone       |
+------------------+
Low Address
```

## Building and Running

### Prerequisites
- CMake (3.10 or higher)
- C++ compiler with C++11 support
- x86_64 architecture (for System V ABI compliance)

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
./examples/task2
```

### Debugging
For debugging purposes, you can use GDB:
```bash
gdb ./examples/task2
```

Useful GDB commands for this example:
- `break foo` - Break at foo function entry
- `info frame` - Examine stack frame
- `x/32x $rsp` - Examine stack contents
- `p $rsp` - Print stack pointer value

## Performance Considerations

1. **Stack Management**:
   - Stack allocation size (4KB is typical)
   - Cache alignment implications
   - Red zone overhead

2. **Context Switching Overhead**:
   - Register state copying
   - Stack pointer manipulation
   - Memory access patterns

## Common Pitfalls

1. **Stack Alignment**:
   - Incorrect alignment can cause crashes
   - SSE/AVX instructions require proper alignment
   - Function calls expect aligned stack

2. **Stack Size**:
   - Too small stack can overflow
   - Too large stack wastes memory
   - Need to consider function call depth

3. **Red Zone Usage**:
   - Signal handlers must not use red zone
   - Interrupt handlers must avoid red zone
   - Some functions may require more scratch space 