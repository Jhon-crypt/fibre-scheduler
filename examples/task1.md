# Task 1: Basic Context Switching Example

This example demonstrates the fundamental concepts of context switching using the fiber scheduler's context management functionality. It serves as a foundational example for understanding how fiber-based cooperative multitasking works.

## Overview

The program showcases a simple context switching scenario that implements a basic form of control flow manipulation using context saving and restoration. This is a fundamental building block for implementing fiber-based concurrency.

Key concepts demonstrated:
1. Context object creation and management
2. Basic context switching operations
3. State preservation between context switches
4. Control flow manipulation
5. Safe termination of context switching sequences

## Technical Background

### Context Switching

Context switching is the process of saving and restoring the execution state of a program. In this implementation:
- The CPU register state is saved to memory
- The stack pointer is preserved
- The instruction pointer is managed to control execution flow

### Memory Considerations

The context switch operation involves:
- Stack memory management
- Register state preservation
- Proper alignment of memory structures
- Prevention of optimization-related issues through volatile variables

## Code Explanation

```cpp
#include "../fibers/context.hpp"
#include <iostream>
#include <cstdlib>

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

### Key Components Detailed Analysis:

#### 1. Context Object
```cpp
Context ctx;
```
- Creates a context structure that holds:
  - CPU register states
  - Stack pointer information
  - Other architecture-specific state data

#### 2. State Management
```cpp
volatile int x = 0;
```
- `volatile` keyword prevents compiler optimization
- Ensures the variable is read from memory each time
- Critical for maintaining correct state across context switches

#### 3. Context Operations
```cpp
get_context(&ctx)
```
- Returns 0 on initial call
- Returns the value passed to `set_context()` on context restoration
- Saves current execution state including:
  - Register values
  - Stack pointer
  - Instruction pointer

```cpp
set_context(&ctx)
```
- Restores previously saved context
- Resumes execution from the point of the last `get_context()`
- Manages stack unwinding

### Program Flow Detailed Breakdown:

1. **Initial Setup**:
   - Context object is created
   - State variable `x` is initialized to 0

2. **First Execution Path**:
   - `get_context()` returns 0
   - `x` is incremented to 1
   - First "a message" is printed
   - Context is switched back using `set_context()`

3. **Second Execution Path**:
   - Execution resumes at `get_context()`
   - `x` is incremented to 2
   - Second "a message" is printed
   - Program continues to completion

4. **Termination**:
   - No more context switches occur
   - Program exits normally

## Expected Output

```
a message
a message
```

### Output Analysis:
- First message: Printed before the context switch
- Second message: Printed after context restoration
- The identical messages demonstrate successful context preservation

## Common Pitfalls and Solutions

1. **Infinite Loops**:
   - Problem: Unrestricted context switching can create infinite loops
   - Solution: Use counter (`x`) to limit switches

2. **Optimization Issues**:
   - Problem: Compiler optimizations can break context switching
   - Solution: Use `volatile` for state variables

3. **Stack Corruption**:
   - Problem: Improper stack management during context switch
   - Solution: Proper context structure alignment and stack pointer preservation

## Advanced Usage

This basic example can be extended to:
1. Implement cooperative multitasking
2. Create fiber pools
3. Build async/await patterns
4. Implement generators/coroutines

## Building and Running

### Prerequisites
- CMake (3.10 or higher)
- C++ compiler with C++11 support
- Make build system

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
./examples/task1
```

### Debugging
For debugging purposes, you can use GDB:
```bash
gdb ./examples/task1
```

Common GDB commands for this example:
- `break main` - Set breakpoint at main
- `watch x` - Watch the counter variable
- `info registers` - Check register states

## Performance Considerations

1. **Context Switch Overhead**:
   - Register saving/restoring time
   - Memory operations cost
   - Cache implications

2. **Memory Usage**:
   - Context structure size
   - Stack memory requirements
   - Cache line considerations
