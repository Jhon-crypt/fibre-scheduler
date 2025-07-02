#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <chrono>
#include <string>
#include <functional>
#include <vector>
#include <iostream>

class Benchmark {
public:
    // Function to measure execution time of a void function
    template<typename Func>
    static auto measure(Func&& func) {
        using namespace std::chrono;
        
        auto start = high_resolution_clock::now();
        std::forward<Func>(func)();
        auto end = high_resolution_clock::now();
        
        return duration_cast<microseconds>(end - start);
    }
    
    // Function to run multiple iterations and get average time
    template<typename Func>
    static auto measure_average(Func&& func, size_t iterations) {
        using namespace std::chrono;
        
        microseconds total(0);
        for (size_t i = 0; i < iterations; ++i) {
            total += measure(func);
        }
        
        return microseconds(total.count() / iterations);
    }
    
    // Struct to hold benchmark results
    struct Result {
        std::string name;
        std::chrono::microseconds time;
        size_t iterations;
        
        Result(const std::string& n, std::chrono::microseconds t, size_t i)
            : name(n), time(t), iterations(i) {}
    };
    
    // Function to run and record a benchmark
    template<typename Func>
    static Result run(const std::string& name, Func&& func, size_t iterations = 1) {
        auto time = measure_average(std::forward<Func>(func), iterations);
        return Result(name, time, iterations);
    }
    
    // Function to print benchmark results
    static void print_result(const Result& result) {
        std::cout << result.name << ": "
                  << result.time.count() << " microseconds "
                  << "(averaged over " << result.iterations << " iterations)"
                  << std::endl;
    }
};

#endif // BENCHMARK_HPP 