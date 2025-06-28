# Fiber Scheduler

A lightweight C++17 fiber scheduler implementation for cooperative multitasking, using setjmp/longjmp for portable context switching.

## Features

- Lightweight context switching using standard C++ library (setjmp/longjmp)
- Works on both x86_64 and ARM64 architectures
- Header-only implementation
- C++17 compliant

## Requirements

- C++17 compatible compiler (tested with Clang++)
- Standard C++ library

## Building

You can build the project using either CMake or directly with clang++.

### Using CMake

```bash
mkdir build
cd build
cmake ..
make
```

### Using Clang++ Directly

To build and run the test program:

```bash
# Compile
clang++ -std=c++17 -c fibers/test_context.cpp

# Link and create executable
clang++ -std=c++17 test_context.o -o test_context

# Run the test
./test_context
```

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

## License

MIT License 