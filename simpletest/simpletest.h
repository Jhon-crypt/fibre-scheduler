#ifndef SIMPLETEST_H
#define SIMPLETEST_H

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <iomanip>

class TestFixture {
public:
    enum Verbosity {
        Quiet,
        Verbose
    };

    struct TestResult {
        std::string message;
        bool passed;
        std::string value;
    };

    static std::vector<TestResult> current_test_results;
    static std::string current_test_name;

    static bool ExecuteTestGroup(const char* group, Verbosity verbosity = Verbose) {
        std::cout << "\n=== Running test group: " << group << " ===\n" << std::endl;
        bool all_passed = true;
        
        for (const auto& result : current_test_results) {
            if (verbosity == Verbose) {
                std::cout << std::setw(50) << std::left << result.message;
                if (result.passed) {
                    std::cout << "\033[32m[PASSED]\033[0m";
                    if (!result.value.empty()) {
                        std::cout << " Value: " << result.value;
                    }
                } else {
                    std::cout << "\033[31m[FAILED]\033[0m";
                    if (!result.value.empty()) {
                        std::cout << " Expected different value. Got: " << result.value;
                    }
                }
                std::cout << std::endl;
            }
            all_passed &= result.passed;
        }

        std::cout << "\nTest group summary:" << std::endl;
        std::cout << "Total tests: " << current_test_results.size() << std::endl;
        int passed = std::count_if(current_test_results.begin(), current_test_results.end(),
                                 [](const TestResult& r) { return r.passed; });
        std::cout << "Passed: " << passed << std::endl;
        std::cout << "Failed: " << (current_test_results.size() - passed) << std::endl;
        
        current_test_results.clear();
        return all_passed;
    }

    static void AddTestResult(const std::string& message, bool passed, const std::string& value = "") {
        current_test_results.push_back({message, passed, value});
    }
};

std::vector<TestFixture::TestResult> TestFixture::current_test_results;
std::string TestFixture::current_test_name;

#define DEFINE_TEST_G(name, group) \
    void TEST_##name##_##group()

#define TEST_MESSAGE(condition, message) \
    TestFixture::AddTestResult(message, condition)

#define TEST_EQUAL(actual, expected, message) \
    { \
        auto a = actual; \
        auto e = expected; \
        bool passed = (a == e); \
        std::ostringstream value; \
        value << a; \
        TestFixture::AddTestResult(message, passed, value.str()); \
    }

#endif // SIMPLETEST_H 