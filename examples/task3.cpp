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

// Test functions
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