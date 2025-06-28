#include "bump_allocator.hpp"
#include <iostream>
#include <chrono>
#include <vector>

// Simple test framework
#define TEST(name) void name()
#define ASSERT(condition) \
    do { \
        if (!(condition)) { \
            std::cerr << "Assertion failed: " << #condition << std::endl; \
            std::cerr << "  at " << __FILE__ << ":" << __LINE__ << std::endl; \
            exit(1); \
        } \
    } while (0)

// Test 5.1: Allocate and Use Objects
TEST(test_basic_allocation) {
    std::cout << "\n=== Test 5.1: Allocate and Use Objects ===\n";
    bump<1024> allocator;
    
    int* x = allocator.alloc<int>(10);
    ASSERT(x != nullptr);
    
    // Test if memory is usable
    for (int i = 0; i < 10; i++) {
        x[i] = i;
    }
    
    for (int i = 0; i < 10; i++) {
        ASSERT(x[i] == i);
    }
    
    std::cout << "Basic allocation test passed\n";
}

// Test 5.2: Over-Allocation Returns nullptr
TEST(test_over_allocation) {
    std::cout << "\n=== Test 5.2: Over-Allocation Returns nullptr ===\n";
    bump<1024> allocator;
    
    int* y = allocator.alloc<int>(1000);
    ASSERT(y == nullptr);
    
    std::cout << "Over-allocation test passed\n";
}

// Test 5.3: Dealloc + Reset
TEST(test_dealloc_reset) {
    std::cout << "\n=== Test 5.3: Dealloc + Reset ===\n";
    bump<1024> allocator;
    
    // First allocation
    int* x = allocator.alloc<int>(10);
    ASSERT(x != nullptr);
    size_t pos_after_first = allocator.get_current_pos();
    
    // Deallocate
    allocator.dealloc();
    ASSERT(allocator.get_allocation_count() == 0);
    ASSERT(allocator.get_current_pos() == 0);
    
    // Try allocating again
    int* y = allocator.alloc<int>(10);
    ASSERT(y != nullptr);
    ASSERT(allocator.get_current_pos() == pos_after_first);
    
    std::cout << "Dealloc and reset test passed\n";
}

// Test 6.1: Benchmark Bump-Up vs Bump-Down
void benchmark_allocations() {
    std::cout << "\n=== Test 6.1: Benchmark Allocations ===\n";
    constexpr size_t small_size = 8;
    constexpr size_t medium_size = 64;
    constexpr size_t large_size = 512;
    constexpr size_t iterations = 1000;
    
    bump<1024*1024> allocator;  // 1MB allocator
    
    // Benchmark small allocations
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; i++) {
        auto ptr = allocator.alloc<uint8_t>(small_size);
        ASSERT(ptr != nullptr);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto small_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    
    // Reset allocator
    while (allocator.get_allocation_count() > 0) {
        allocator.dealloc();
    }
    
    // Benchmark medium allocations
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; i++) {
        auto ptr = allocator.alloc<uint8_t>(medium_size);
        ASSERT(ptr != nullptr);
    }
    end = std::chrono::high_resolution_clock::now();
    auto medium_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    
    // Reset allocator
    while (allocator.get_allocation_count() > 0) {
        allocator.dealloc();
    }
    
    // Benchmark large allocations
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; i++) {
        auto ptr = allocator.alloc<uint8_t>(large_size);
        ASSERT(ptr != nullptr);
    }
    end = std::chrono::high_resolution_clock::now();
    auto large_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    
    std::cout << "Benchmark results for " << iterations << " iterations:\n";
    std::cout << "Small allocations (" << small_size << " bytes): " << small_time << " µs\n";
    std::cout << "Medium allocations (" << medium_size << " bytes): " << medium_time << " µs\n";
    std::cout << "Large allocations (" << large_size << " bytes): " << large_time << " µs\n";
}

int main() {
    test_basic_allocation();
    test_over_allocation();
    test_dealloc_reset();
    benchmark_allocations();
    return 0;
} 