#ifndef BUMP_ALLOCATOR_HPP
#define BUMP_ALLOCATOR_HPP

#include <cstddef>
#include <cstdint>
#include <type_traits>

template<size_t Size>
class bump {
private:
    alignas(std::max_align_t) uint8_t buffer[Size];
    size_t current_pos = 0;
    size_t allocation_count = 0;

public:
    template<typename T>
    T* alloc(size_t count = 1) {
        // Calculate required alignment
        size_t align = alignof(T);
        size_t padding = (align - (current_pos % align)) % align;
        size_t required_size = sizeof(T) * count + padding;
        
        // Check if we have enough space
        if (current_pos + required_size > Size) {
            return nullptr;
        }
        
        // Apply padding
        current_pos += padding;
        
        // Get pointer to allocated memory
        T* result = reinterpret_cast<T*>(&buffer[current_pos]);
        
        // Update position and count
        current_pos += sizeof(T) * count;
        allocation_count++;
        
        return result;
    }
    
    void dealloc() {
        if (allocation_count > 0) {
            allocation_count--;
            if (allocation_count == 0) {
                current_pos = 0;  // Reset only when all allocations are deallocated
            }
        }
    }
    
    // For testing/debugging
    size_t get_current_pos() const { return current_pos; }
    size_t get_allocation_count() const { return allocation_count; }
    size_t get_available_space() const { return Size - current_pos; }
};

#endif // BUMP_ALLOCATOR_HPP 