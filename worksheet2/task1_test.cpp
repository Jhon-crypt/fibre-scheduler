#include "task1.hpp"
#include <iostream>
#include <string>

// Test different allocation sizes
void test_different_sizes() {
    std::cout << "Testing different allocation sizes..." << std::endl;
    
    BumpAllocator<1024> allocator;
    
    // Allocate an int
    int* i = allocator.alloc<int>();
    if (i != nullptr) {
        *i = 42;
        std::cout << "Allocated int: " << *i << std::endl;
    }
    
    // Allocate a double
    double* d = allocator.alloc<double>();
    if (d != nullptr) {
        *d = 3.14;
        std::cout << "Allocated double: " << *d << std::endl;
    }
    
    // Allocate an array of chars
    char* str = allocator.alloc<char>(10);
    if (str != nullptr) {
        strcpy(str, "Hello");
        std::cout << "Allocated string: " << str << std::endl;
    }
    
    std::cout << "Remaining space: " << allocator.remaining_space() << " bytes" << std::endl;
}

// Test allocation failure
void test_allocation_failure() {
    std::cout << "\nTesting allocation failure..." << std::endl;
    
    BumpAllocator<16> small_allocator;
    
    // Try to allocate more than available
    int* arr = small_allocator.alloc<int>(5);  // 20 bytes needed
    if (arr == nullptr) {
        std::cout << "Allocation failed as expected" << std::endl;
    }
}

// Test allocator reset
void test_allocator_reset() {
    std::cout << "\nTesting allocator reset..." << std::endl;
    
    BumpAllocator<64> allocator;
    
    // Make some allocations
    int* i1 = allocator.alloc<int>();
    int* i2 = allocator.alloc<int>();
    
    std::cout << "Number of allocations: " << allocator.allocations() << std::endl;
    std::cout << "Remaining space before dealloc: " << allocator.remaining_space() << std::endl;
    
    // Deallocate
    allocator.dealloc();
    allocator.dealloc();
    
    std::cout << "After deallocating all, remaining space: " << allocator.remaining_space() << std::endl;
    
    // Try new allocation after reset
    int* i3 = allocator.alloc<int>();
    if (i3 != nullptr) {
        *i3 = 100;
        std::cout << "Successfully allocated after reset: " << *i3 << std::endl;
    }
}

int main() {
    test_different_sizes();
    test_allocation_failure();
    test_allocator_reset();
    
    return 0;
} 