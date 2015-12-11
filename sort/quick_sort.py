import random

def quick_sort(arr):
    if(len(arr) <= 1):
        return arr

    pivot = arr[0]
    left = []
    right = []
    for i in range(1, len(arr)):
        if(arr[i] > pivot):
            right.append(arr[i])
        else:
            left.append(arr[i])

    return quick_sort(left) + [pivot] + quick_sort(right)
