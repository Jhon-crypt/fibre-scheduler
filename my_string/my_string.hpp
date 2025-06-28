#ifndef MY_STRING_HPP
#define MY_STRING_HPP

#include <cstring>
#include <iostream>

class my_string {
private:
    struct Data {
        char* str;
        int ref_count;
        
        Data(const char* s) : ref_count(1) {
            str = new char[strlen(s) + 1];
            strcpy(str, s);
        }
        
        ~Data() {
            delete[] str;
        }
    };
    
    Data* data;
    
public:
    my_string(const char* s) : data(new Data(s)) {
        std::cout << "[" << data->ref_count << "]" << std::endl;
    }
    
    my_string(const my_string& other) : data(other.data) {
        data->ref_count++;
        std::cout << "[" << data->ref_count << "]" << std::endl;
    }
    
    ~my_string() {
        data->ref_count--;
        std::cout << "[" << data->ref_count << "]" << std::endl;
        if (data->ref_count == 0) {
            delete data;
        }
    }
    
    my_string& operator=(const my_string& other) {
        if (this != &other) {
            data->ref_count--;
            if (data->ref_count == 0) {
                delete data;
            }
            data = other.data;
            data->ref_count++;
        }
        return *this;
    }
    
    void setChar(int index, char c) {
        if (data->ref_count > 1) {
            // Copy-on-write: create a new copy if shared
            Data* new_data = new Data(data->str);
            data->ref_count--;
            data = new_data;
        }
        data->str[index] = c;
    }
    
    void print() const {
        std::cout << data->str << std::endl;
    }
    
    int get_ref_count() const {
        return data->ref_count;
    }
};

// Template wrapper for reference counting
template<typename T>
class RefCounted {
private:
    struct Data {
        T* obj;
        int ref_count;
        
        Data(const T& t) : ref_count(1) {
            obj = new T(t);
        }
        
        ~Data() {
            delete obj;
        }
    };
    
    Data* data;
    
public:
    RefCounted(const T& t) : data(new Data(t)) {}
    
    RefCounted(const RefCounted& other) : data(other.data) {
        data->ref_count++;
    }
    
    ~RefCounted() {
        data->ref_count--;
        if (data->ref_count == 0) {
            delete data;
        }
    }
    
    RefCounted& operator=(const RefCounted& other) {
        if (this != &other) {
            data->ref_count--;
            if (data->ref_count == 0) {
                delete data;
            }
            data = other.data;
            data->ref_count++;
        }
        return *this;
    }
    
    T* operator->() {
        if (data->ref_count > 1) {
            // Copy-on-write
            Data* new_data = new Data(*data->obj);
            data->ref_count--;
            data = new_data;
        }
        return data->obj;
    }
    
    const T* operator->() const {
        return data->obj;
    }
    
    int get_ref_count() const {
        return data->ref_count;
    }
};

#endif // MY_STRING_HPP 