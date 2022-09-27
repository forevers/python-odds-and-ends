/*
cc -fPIC -shared -o libctypes_test_c.so ctypes_test_c.c
clang -shared -o libctypes_test_c.so ctypes_test_c.c
*/

#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

int test_c_function(int* int_ptr, size_t size)
{
    int sum = 0;

    for (int i = 0; i < size; i++) {
        sum += int_ptr[i];
    }

    return sum;
}

void test_c_callback_no_ret(void (*functionPtr)(int), int sleep_sec)
{
    printf("test_c_callback_no_ret entry: %d\n", sleep_sec);
    for (int i = 0; i < sleep_sec; i++) {
       sleep(1);
       printf("slept %d seconds\n", i);
    }

    // python callback function
    functionPtr(sleep_sec);
}
