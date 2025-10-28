L1 = list(map(int, input("Enter elements of List L1 separated by space: ").split()))
L2 = list(map(int, input("Enter elements of List L2 separated by space: ").split()))

L3 = L1 + L2
print("Combined List L3:", L3)
print("Odd index values from L3:", [L3[i] for i in range(1, len(L3), 2)])

def merge_sort(arr):
    if len(arr) > 1:
        mid = len(arr) // 2
        left = arr[:mid]
        right = arr[mid:]
        merge_sort(left)
        merge_sort(right)
        i = j = k = 0
        while i < len(left) and j < len(right):
            if left[i] < right[j]:
                arr[k] = left[i]
                i += 1
            else:
                arr[k] = right[j]
                j += 1
            k += 1
        while i < len(left):
            arr[k] = left[i]
            i += 1
            k += 1
        while j < len(right):
            arr[k] = right[j]
            j += 1
            k += 1
    return arr

L4 = merge_sort(L1 + L2)
print("Sorted List L4 (Merge Sort):", L4)
