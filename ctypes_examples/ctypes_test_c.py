import ctypes
_test_c_module = ctypes.CDLL('./libctypes_test_c.so')
_test_c_module.test_c_function.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_size_t)


def test_c_function_wrapper(numbers: list) -> int:
    """
    :param numbers: list of integers to sum
    :return: integer sum
    test native shared library summing code
    """

    global _test_c_module
    list_len = len(numbers)
    # define native array mapping
    ctypes_array = ctypes.c_int * list_len
    # native call
    result = _test_c_module.test_c_function(ctypes_array(*numbers), ctypes.c_size_t(list_len))

    return int(result)


print('ctypes POINTER BUFFER TEST')
test_list = [1, 2, 3, 4, 5]
test_list_sum = test_c_function_wrapper(test_list)
print(f'sum: {test_list_sum}')


@ctypes.CFUNCTYPE(None, ctypes.c_int)
def sleep_callback(sleep_sec: int):
    print(f'libctypes_test_c method has finished its {sleep_sec} second sleep')


print('ctypes PYTHON CALLBACK FROM NATIVE FUNCTION TEST')
sleep = 5
print(f'pre {sleep} second native sleep')
_test_c_module.test_c_callback_no_ret(sleep_callback, int(4))
print(f'post {sleep} second native sleep')
