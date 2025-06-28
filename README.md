# Fiber Scheduler

A lightweight C++17 fiber scheduler implementation for cooperative multitasking, using setjmp/longjmp for portable context switching.

## Features

- Lightweight context switching using standard C++ library (setjmp/longjmp)
- Cross-platform support (Windows, macOS, Linux)
- Works on multiple architectures (x86_64, ARM64)
- Header-only implementation
- C++17 compliant
- Reference-counted string with copy-on-write
- Template-based reference counting wrapper
- Efficient bump allocator

## Requirements

- C++17 compatible compiler:
  - Windows: MSVC, MinGW-w64, or Clang
  - macOS: Clang++
  - Linux: GCC or Clang++
- Standard C++ library
- CMake 3.15+ (if building with CMake)

## Building and Running Tests

### Using CMake (Recommended for all platforms)

```bash
mkdir build
cd build
cmake ..
```

Then:
- On Unix-like systems (macOS/Linux):
  ```bash
  make
  ```
- On Windows with MSVC:
  ```bash
  cmake --build .
  ```

### Using Clang++ Directly

You can also build and run each test file directly:

```bash
# Context Switching Tests
cd fibers
clang++ -std=c++17 test_context.cpp -o test_context
./test_context

clang++ -std=c++17 test_suite.cpp -o test_suite
./test_suite

# Reference-Counted String Tests
cd ../my_string
clang++ -std=c++17 test_my_string.cpp -o test_my_string
./test_my_string

# Bump Allocator Tests
cd ../allocator
clang++ -std=c++17 test_bump_allocator.cpp -o test_bump_allocator
./test_bump_allocator
```

## Test Coverage

### Context Switching (fibers/test_context.cpp, fibers/test_suite.cpp)
- Basic context save/restore
- Function execution with context switching
- Sequential function execution
- Data sharing between functions
- Function sequencing with before/after states

### Reference Counting (my_string/test_my_string.cpp)
- String sharing and scope management
- Reference count tracking
- Copy-on-write behavior
- Memory cleanup on reference count zero
- Template wrapper for generic types

### Memory Management (allocator/test_bump_allocator.cpp)
- Basic allocation and usage
- Over-allocation handling
- Deallocation and reset functionality
- Performance benchmarking for different allocation sizes

## Usage

The library provides three main functions for context switching:

```cpp
#include "fibers/context.hpp"

// Save current context to ctx and return 0
int get_context(Context* ctx);

// Load context from ctx (doesn't return)
void set_context(Context* ctx);

// Save current context to old_ctx, then load context from new_ctx
void swap_context(Context* old_ctx, Context* new_ctx);
```

### Example

```cpp
#include "fibers/context.hpp"
#include <iostream>

Context ctx;
volatile int x = 0;

if (get_context(&ctx) == 0) {
    x++;
    if (x < 2) {
        std::cout << "Before context switch" << std::endl;
        set_context(&ctx);
    }
}
std::cout << "After context switch" << std::endl;
```

## Platform-Specific Notes

### Windows
- Uses `__declspec(noreturn)` instead of `[[noreturn]]` for MSVC compatibility
- Works with both MSVC and MinGW-w64 compilers
- Tested on both x86_64 and ARM64 Windows

### macOS
- Works natively on both Intel (x86_64) and Apple Silicon (ARM64) Macs
- Uses Clang's implementation of setjmp/longjmp

### Linux
- Works on both x86_64 and ARM64 architectures
- Compatible with both GCC and Clang compilers

## License

MIT License 