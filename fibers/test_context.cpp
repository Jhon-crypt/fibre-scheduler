#include "context.hpp"
#include <iostream>
#include <cstdlib>
#include <cstring>

// Global contexts for switching between main and foo
Context main_ctx;
Context foo_ctx;

// Function to be executed in foo's context
void foo() {
    std::cout << "Executing foo()" << std::endl;
    // Switch back to main context
    set_context(&main_ctx);
}

int main() {
    // Test 1: Basic context save/restore
    std::cout << "Test 1: Basic context switching\n";
    Context ctx;
    volatile int x = 0;
    
    if (get_context(&ctx) == 0) {
        x++;
        if (x < 2) {
            std::cout << "Before context switch, x = " << x << std::endl;
            set_context(&ctx);
        }
    }
    std::cout << "After context switch, x = " << x << std::endl;
    
    // Test 2: Context switching between functions
    std::cout << "\nTest 2: Context switching between functions\n";
    
    // Save main's context
    if (get_context(&main_ctx) == 0) {
        // First time through - call foo
        foo();
    }
    
    std::cout << "Back in main()" << std::endl;
    return 0;
} 