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