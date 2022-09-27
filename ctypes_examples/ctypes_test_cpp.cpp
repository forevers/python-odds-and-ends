/*
g++ -shared -std=c++20 -o ctypes_test_cpp ctypes_test_cpp.cpp
clang++ -shared -std=c++20 -I. -Wall ctypes_test_cpp.cpp -o libctypes_test_cpp.so
*/

#include <stddef.h>

#include <chrono>
#include <iostream>
#include <thread>

// ctypes works with C library interface
extern "C" {
    int test_c_function(int* int_ptr, size_t size);
    void test_c_callback_no_ret(void (*functionPtr)(int), int sleep_sec);
}


using namespace std;

class TestClass
{
public:
    TestClass() : sleep_sec_ {5} {};
    TestClass(int sleep_sec) : sleep_sec_ {sleep_sec} {};

    int TestCppFunction(int* int_ptr, size_t size)
    {
        cout<<"TestCppFunction()"<<endl;
        int sum = 0;
        for (int i = 0; i < size; i++) {
            sum += int_ptr[i];
        }
        return sum;
    }

    void test_cpp_callback_no_ret(int sleep_sec)
    {
        sleep_sec_ = sleep_sec;
        printf("test_cpp_callback_no_ret entry: %d\n", sleep_sec_);
        for (int i = 0; i < sleep_sec_; i++) {
           std::this_thread::sleep_for(std::chrono::milliseconds(1000));
           printf("slept %d seconds\n", i);
        }
    }

private:
    int sleep_sec_;
};

int test_c_function(int* int_ptr, size_t size)
{
    TestClass test_class {};
    return test_class.TestCppFunction(int_ptr, size);
}

void test_c_callback_no_ret(void (*functionPtr)(int), int sleep_sec)
{
    TestClass test_class {};
    test_class.test_cpp_callback_no_ret(sleep_sec);
    // python callback function
    functionPtr(sleep_sec);
}
