#include "context.hpp"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cassert>

// Test 1.1: Save and Restore Context
void test_save_restore_context() {
    std::cout << "\n=== Test 1.1: Save and Restore Context ===\n";
    volatile int x = 0;
    Context c;
    
    if (get_context(&c) == 0) {
        std::cout << "Message\n";
        if (x == 0) {
            x += 1;
            set_context(&c);
        }
    }
}

// Test 1.2: Jump to Function
void foo() {
    std::cout << "you called foo\n";
}

void test_jump_to_function() {
    std::cout << "\n=== Test 1.2: Jump to Function ===\n";
    foo();
}

// Test 2.1: Two Functions Sequential
void func1() {
    std::cout << "fiber 1\n";
}

void func2() {
    std::cout << "fiber 2\n";
}

void test_two_functions() {
    std::cout << "\n=== Test 2.1: Two Functions Sequential ===\n";
    func1();
    func2();
}

// Test 2.2: Function with Data
int shared_data = 10;

void func1_with_data() {
    std::cout << "fiber 1: " << shared_data << std::endl;
    shared_data += 1;
}

void func2_with_data() {
    std::cout << "fiber 2: " << shared_data << std::endl;
}

void test_function_with_data() {
    std::cout << "\n=== Test 2.2: Function with Data ===\n";
    func1_with_data();
    func2_with_data();
}

// Test 3.1: Function Sequence
void func1_sequence() {
    std::cout << "fiber 1 before\n";
    std::cout << "fiber 1 after\n";
}

void func2_sequence() {
    std::cout << "fiber 2\n";
}

void test_function_sequence() {
    std::cout << "\n=== Test 3.1: Function Sequence ===\n";
    func1_sequence();
    func2_sequence();
}

int main() {
    // Run all tests
    test_save_restore_context();
    test_jump_to_function();
    test_two_functions();
    test_function_with_data();
    test_function_sequence();
    
    return 0;
} 