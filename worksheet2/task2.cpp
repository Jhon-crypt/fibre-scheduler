#include "task1.hpp"
#include <simpletest.h>
#include <iostream>
#include <sstream>

// Forward declarations of test functions
void TEST_BasicAllocation_BumpAllocator();
void TEST_AllocationFailure_BumpAllocator();
void TEST_MultipleAllocations_BumpAllocator();
void TEST_DeallocationReset_BumpAllocator();
void TEST_RemainingSpace_BumpAllocator();

// Test group definitions
struct TestGroup {
    const char* name;
    std::vector<std::function<void()>> tests;
};

TestGroup test_groups[] = {
    {
        "BumpAllocator",
        {
            TEST_BasicAllocation_BumpAllocator,
            TEST_AllocationFailure_BumpAllocator,
            TEST_MultipleAllocations_BumpAllocator,
            TEST_DeallocationReset_BumpAllocator,
            TEST_RemainingSpace_BumpAllocator
        }
    }
};

// Test basic allocation
DEFINE_TEST_G(BasicAllocation, BumpAllocator) {
    BumpAllocator<1024> allocator;
    
    int* x = allocator.alloc<int>();
    TEST_MESSAGE(x != nullptr, "Basic int allocation should succeed");
    
    if (x != nullptr) {
        *x = 42;
        TEST_EQUAL(*x, 42, "Allocated memory should store and retrieve values correctly");
    }
    
    TEST_EQUAL(allocator.allocations(), 1, "Allocation counter should be 1");
}

// Test allocation failure
DEFINE_TEST_G(AllocationFailure, BumpAllocator) {
    BumpAllocator<4> small_allocator;  // Only 4 bytes
    
    int* x = small_allocator.alloc<int>();
    TEST_MESSAGE(x != nullptr, "Should be able to allocate 4 bytes");
    
    int* y = small_allocator.alloc<int>();
    TEST_MESSAGE(y == nullptr, "Should fail to allocate beyond capacity");
    
    TEST_EQUAL(small_allocator.remaining_space(), 0, "Should have no remaining space");
}

// Test multiple allocations
DEFINE_TEST_G(MultipleAllocations, BumpAllocator) {
    BumpAllocator<100> allocator;
    
    int* x = allocator.alloc<int>();
    double* d = allocator.alloc<double>();
    char* c = allocator.alloc<char>(10);
    
    TEST_MESSAGE(x != nullptr, "Int allocation should succeed");
    TEST_MESSAGE(d != nullptr, "Double allocation should succeed");
    TEST_MESSAGE(c != nullptr, "Char array allocation should succeed");
    
    if (x && d && c) {
        *x = 42;
        *d = 3.14;
        c[0] = 'A';
        
        TEST_EQUAL(*x, 42, "Int value should be stored correctly");
        TEST_EQUAL(*d, 3.14, "Double value should be stored correctly");
        TEST_EQUAL(c[0], 'A', "Char value should be stored correctly");
    }
    
    TEST_EQUAL(allocator.allocations(), 3, "Should have 3 allocations");
}

// Test deallocation and reset
DEFINE_TEST_G(DeallocationReset, BumpAllocator) {
    BumpAllocator<64> allocator;
    size_t initial_space = allocator.remaining_space();
    
    int* x = allocator.alloc<int>();
    int* y = allocator.alloc<int>();
    
    TEST_EQUAL(allocator.allocations(), 2, "Should have 2 allocations initially");
    
    allocator.dealloc();
    TEST_EQUAL(allocator.allocations(), 1, "Should have 1 allocation after first dealloc");
    
    allocator.dealloc();
    TEST_EQUAL(allocator.allocations(), 0, "Should have 0 allocations after second dealloc");
    
    // After all deallocations, should be able to allocate again
    int* z = allocator.alloc<int>();
    TEST_MESSAGE(z != nullptr, "Should be able to allocate after reset");
    
    if (z != nullptr) {
        *z = 100;
        TEST_EQUAL(*z, 100, "New allocation should work correctly after reset");
    }
    
    TEST_EQUAL(allocator.remaining_space(), initial_space - sizeof(int), 
               "Should have correct remaining space after reset and new allocation");
}

// Test remaining space calculations
DEFINE_TEST_G(RemainingSpace, BumpAllocator) {
    BumpAllocator<100> allocator;
    size_t initial_space = allocator.remaining_space();
    
    TEST_EQUAL(initial_space, 100, "Initial space should be 100 bytes");
    
    int* x = allocator.alloc<int>();
    TEST_EQUAL(allocator.remaining_space(), initial_space - sizeof(int),
               "Remaining space should decrease by sizeof(int)");
    
    double* d = allocator.alloc<double>();
    TEST_EQUAL(allocator.remaining_space(), initial_space - sizeof(int) - sizeof(double),
               "Remaining space should decrease by sizeof(double)");
}

int main() {
    bool pass = true;
    
    for (const auto& group : test_groups) {
        std::cout << "\nRunning test group: " << group.name << "\n";
        for (const auto& test : group.tests) {
            test();
        }
        pass &= TestFixture::ExecuteTestGroup(group.name, TestFixture::Verbose);
    }
    
    return pass ? 0 : 1;
} 