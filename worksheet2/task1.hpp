#ifndef BUMP_ALLOCATOR_HPP
#define BUMP_ALLOCATOR_HPP

#include <cstddef>
#include <cstdint>

template<size_t N>
class BumpAllocator {
private:
    char memory_[N];           // Fixed size memory chunk
    char* next_;               // Bump pointer
    size_t allocations_;       // Counter for allocations

public:
    BumpAllocator() : next_(memory_), allocations_(0) {}

    template<typename T>
    T* alloc(size_t n = 1) {
        // Calculate total size needed
        size_t size = sizeof(T) * n;
        
        // Check if we have enough space
        if (next_ + size > memory_ + N) {
            return nullptr;
        }

        // Save current position
        T* result = reinterpret_cast<T*>(next_);
        
        // Bump the pointer
        next_ += size;
        
        // Increment allocation counter
        ++allocations_;
        
        return result;
    }

    void dealloc() {
        // Decrement allocation counter
        if (allocations_ > 0) {
            --allocations_;
            
            // If all allocations are freed, reset the bump pointer
            if (allocations_ == 0) {
                next_ = memory_;
            }
        }
    }

    // Static method to get the total capacity
    static constexpr size_t capacity() {
        return N;
    }

    // Method to get current number of allocations
    size_t allocations() const {
        return allocations_;
    }

    // Method to get remaining space
    size_t remaining_space() const {
        return N - (next_ - memory_);
    }
};

#endif // BUMP_ALLOCATOR_HPP 