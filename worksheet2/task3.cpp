#include "task3.hpp"
#include "task1.hpp"
#include <iostream>
#include <vector>
#include <memory>

// Bump allocator that grows upward
template<size_t N>
class BumpUpAllocator : public BumpAllocator<N> {};

// Bump allocator that grows downward
template<size_t N>
class BumpDownAllocator {
private:
    char memory_[N];
    char* next_;
    size_t allocations_;

public:
    BumpDownAllocator() : next_(memory_ + N), allocations_(0) {}

    template<typename T>
    T* alloc(size_t n = 1) {
        size_t size = sizeof(T) * n;
        
        // Check if we have enough space
        if (next_ - size < memory_) {
            return nullptr;
        }
        
        // Move pointer down
        next_ -= size;
        
        // Increment allocation counter
        ++allocations_;
        
        return reinterpret_cast<T*>(next_);
    }

    void dealloc() {
        if (allocations_ > 0) {
            --allocations_;
            if (allocations_ == 0) {
                next_ = memory_ + N;
            }
        }
    }
};

// Benchmark functions
void benchmark_small_allocations(size_t count) {
    constexpr size_t HEAP_SIZE = 1024 * 1024;  // 1MB heap
    
    // Test BumpUpAllocator
    auto up_test = [count]() {
        BumpUpAllocator<HEAP_SIZE> up_alloc;
        for (size_t i = 0; i < count; ++i) {
            auto ptr = up_alloc.alloc<char>();
            if (ptr) *ptr = 'a';
        }
    };
    
    // Test BumpDownAllocator
    auto down_test = [count]() {
        BumpDownAllocator<HEAP_SIZE> down_alloc;
        for (size_t i = 0; i < count; ++i) {
            auto ptr = down_alloc.alloc<char>();
            if (ptr) *ptr = 'a';
        }
    };
    
    auto up_result = Benchmark::run("BumpUpAllocator - Small Allocations", up_test, 10);
    auto down_result = Benchmark::run("BumpDownAllocator - Small Allocations", down_test, 10);
    
    Benchmark::print_result(up_result);
    Benchmark::print_result(down_result);
}

void benchmark_large_allocations(size_t count) {
    constexpr size_t HEAP_SIZE = 1024 * 1024;  // 1MB heap
    constexpr size_t ALLOC_SIZE = 1024;        // 1KB allocations
    
    // Test BumpUpAllocator
    auto up_test = [count]() {
        BumpUpAllocator<HEAP_SIZE> up_alloc;
        for (size_t i = 0; i < count; ++i) {
            auto ptr = up_alloc.alloc<char>(ALLOC_SIZE);
            if (ptr) ptr[0] = 'a';
        }
    };
    
    // Test BumpDownAllocator
    auto down_test = [count]() {
        BumpDownAllocator<HEAP_SIZE> down_alloc;
        for (size_t i = 0; i < count; ++i) {
            auto ptr = down_alloc.alloc<char>(ALLOC_SIZE);
            if (ptr) ptr[0] = 'a';
        }
    };
    
    auto up_result = Benchmark::run("BumpUpAllocator - Large Allocations", up_test, 10);
    auto down_result = Benchmark::run("BumpDownAllocator - Large Allocations", down_test, 10);
    
    Benchmark::print_result(up_result);
    Benchmark::print_result(down_result);
}

void benchmark_mixed_allocations() {
    constexpr size_t HEAP_SIZE = 1024 * 1024;  // 1MB heap
    
    // Test BumpUpAllocator
    auto up_test = []() {
        BumpUpAllocator<HEAP_SIZE> up_alloc;
        for (size_t i = 0; i < 1000; ++i) {
            if (i % 2 == 0) {
                auto ptr = up_alloc.alloc<char>();
                if (ptr) *ptr = 'a';
            } else {
                auto ptr = up_alloc.alloc<int>();
                if (ptr) *ptr = 42;
            }
        }
    };
    
    // Test BumpDownAllocator
    auto down_test = []() {
        BumpDownAllocator<HEAP_SIZE> down_alloc;
        for (size_t i = 0; i < 1000; ++i) {
            if (i % 2 == 0) {
                auto ptr = down_alloc.alloc<char>();
                if (ptr) *ptr = 'a';
            } else {
                auto ptr = down_alloc.alloc<int>();
                if (ptr) *ptr = 42;
            }
        }
    };
    
    auto up_result = Benchmark::run("BumpUpAllocator - Mixed Allocations", up_test, 10);
    auto down_result = Benchmark::run("BumpDownAllocator - Mixed Allocations", down_test, 10);
    
    Benchmark::print_result(up_result);
    Benchmark::print_result(down_result);
}

int main() {
    std::cout << "Running benchmarks...\n\n";
    
    std::cout << "1. Small Allocations Test (10000 allocations)\n";
    benchmark_small_allocations(10000);
    
    std::cout << "\n2. Large Allocations Test (100 allocations)\n";
    benchmark_large_allocations(100);
    
    std::cout << "\n3. Mixed Allocations Test\n";
    benchmark_mixed_allocations();
    
    return 0;
} 