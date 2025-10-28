import numpy as np

arr = np.array([[[1, 2, 3],
                 [4, 5, 6],
                 [7, 8, 9]],
                [[10, 11, 12],
                 [13, 14, 15],
                 [16, 17, 18]],
                [[19, 20, 21],
                 [22, 23, 24],
                 [25, 26, 27]]])

print("Original Array:\n", arr)

arr[1, 1, 1] = 99
print("After replacing value:\n", arr)

sub_arr = arr[0:2, 0:2, 0:2]
print("Extracted 2x2x2 array:\n", sub_arr)

arr2 = np.ones((3, 3, 3), dtype=int)
added = arr + arr2
print("Addition of two arrays:\n", added)
print("Sum of all elements:", arr.sum())
