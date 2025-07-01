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

### Using CMake (Recommended)

```bash
# Create build directory
mkdir build
cd build

# Configure and build
cmake ..
make

# Run all tests using CTest
ctest --output-on-failure
```

### Running All Tests at Once

After building with CMake, you can run all test executables in sequence:

```bash
# From the build directory
./fibers/test_context && ./fibers/test_suite && ./my_string/test_my_string && ./allocator/test_bump_allocator
```

This will run all tests and show the complete output:
```
Test 1: Basic context switching
Before context switch, x = 1
After context switch, x = 1

Test 2: Context switching between functions
Executing foo()
Back in main()

=== Test 1.1: Save and Restore Context ===
Message

=== Test 1.2: Jump to Function ===
you called foo

=== Test 2.1: Two Functions Sequential ===
fiber 1
fiber 2

=== Test 2.2: Function with Data ===
fiber 1: 10
fiber 2: 11

=== Test 3.1: Function Sequence ===
fiber 1 before
fiber 1 after
fiber 2

=== Test 4.1: my_string Sharing and Scope ===
[1]
[2]
Reference count inside scope: 2
[1]
Reference count after scope: 1
HEllo world
[0]

=== Test 4.2: Reference Count Hits 0 ===
[1]
[2]
Reference count after copy: 2
[1]
Reference count before delete: 1
[0]

=== Test 4.3: Template Wrapper ===
Initial ref count: 1
Ref count after copy: 2
p1.x = 10, p2.x = 30
Ref count after modification: 1
Final ref count: 1

=== Test 5.1: Allocate and Use Objects ===
Basic allocation test passed

=== Test 5.2: Over-Allocation Returns nullptr ===
Over-allocation test passed

=== Test 5.3: Dealloc + Reset ===
Dealloc and reset test passed

=== Test 6.1: Benchmark Allocations ===
Benchmark results for 1000 iterations:
Small allocations (8 bytes): ~10 µs
Medium allocations (64 bytes): ~9 µs
Large allocations (512 bytes): ~10 µs
```

### Running Individual Test Suites

You can also run each test suite individually:

```bash
# Context Switching Tests
./fibers/test_context
# Expected output:
# - Test 1: Basic context switching
# - Test 2: Context switching between functions

./fibers/test_suite
# Expected output:
# - Test 1.1: Save and Restore Context
# - Test 1.2: Jump to Function
# - Test 2.1: Two Functions Sequential
# - Test 2.2: Function with Data
# - Test 3.1: Function Sequence

# Reference-Counted String Tests
./my_string/test_my_string
# Expected output:
# - Test 4.1: my_string Sharing and Scope
# - Test 4.2: Reference Count Hits 0
# - Test 4.3: Template Wrapper

# Bump Allocator Tests
./allocator/test_bump_allocator
# Expected output:
# - Test 5.1: Allocate and Use Objects
# - Test 5.2: Over-Allocation Returns nullptr
# - Test 5.3: Dealloc + Reset
# - Test 6.1: Benchmark Allocations
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

# Run all tests at once
cd ..
./fibers/test_context && ./fibers/test_suite && ./my_string/test_my_string && ./allocator/test_bump_allocator
``` 