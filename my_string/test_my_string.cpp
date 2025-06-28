#include "my_string.hpp"
#include <iostream>

// Test class for RefCounted template
class Point {
public:
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

void test_my_string() {
    std::cout << "\n=== Test 4.1: my_string Sharing and Scope ===\n";
    my_string s("Hello world");
    {
        my_string t = s;
        std::cout << "Reference count inside scope: " << s.get_ref_count() << std::endl;
    }
    std::cout << "Reference count after scope: " << s.get_ref_count() << std::endl;
    s.setChar(1, 'E');
    s.print();  // Should print "HEllo world"
}

void test_ref_count_zero() {
    std::cout << "\n=== Test 4.2: Reference Count Hits 0 ===\n";
    my_string* s = new my_string("Test string");
    {
        my_string t = *s;
        std::cout << "Reference count after copy: " << t.get_ref_count() << std::endl;
    }
    std::cout << "Reference count before delete: " << s->get_ref_count() << std::endl;
    delete s;  // Should show [0] and trigger deallocation
}

void test_template_wrapper() {
    std::cout << "\n=== Test 4.3: Template Wrapper ===\n";
    
    // Create a reference-counted Point
    RefCounted<Point> p1(Point(10, 20));
    std::cout << "Initial ref count: " << p1.get_ref_count() << std::endl;
    
    // Test copy
    {
        RefCounted<Point> p2 = p1;
        std::cout << "Ref count after copy: " << p1.get_ref_count() << std::endl;
        
        // Modify through p2 (should trigger copy-on-write)
        p2->x = 30;
        std::cout << "p1.x = " << p1->x << ", p2.x = " << p2->x << std::endl;
        std::cout << "Ref count after modification: " << p1.get_ref_count() << std::endl;
    }
    
    // Test after p2 is destroyed
    std::cout << "Final ref count: " << p1.get_ref_count() << std::endl;
}

int main() {
    test_my_string();
    test_ref_count_zero();
    test_template_wrapper();
    return 0;
} 