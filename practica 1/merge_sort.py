import random
import time

def merge_sort(arr):
    if len(arr) <= 1:
        return arr

    mid = len(arr) // 2
    left_half = arr[:mid]
    right_half = arr[mid:]

    left_half = merge_sort(left_half)
    right_half = merge_sort(right_half)

    return merge(left_half, right_half)

def merge(left, right):
    result = []
    i = j = 0

    while i < len(left) and j < len(right):
        if left[i] < right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1

    result.extend(left[i:])
    result.extend(right[j:])
    
    return result

def generate_random_list(n, min_val, max_val):
    return [random.randint(min_val, max_val) for _ in range(n)]

# Ejemplo de uso:

tiempo_inicial=time.time()
unsorted_list = generate_random_list(50000, 0, 10000)
print("Lista original:", unsorted_list)
sorted_list = merge_sort(unsorted_list)
print("Lista ordenada:",sorted_list)
tiempo_final = time.time()
execution_time=tiempo_final-tiempo_inicial
print("Tiempo de ejecución:", execution_time, "segundos")
