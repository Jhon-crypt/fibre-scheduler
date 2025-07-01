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