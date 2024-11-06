import time
import random
import bisect

def binary_search(arr, target):
    """Perform binary search on a sorted array."""
    low, high = 0, len(arr) - 1
    while low <= high:
        mid = (low + high) // 2
        if arr[mid] < target:
            low = mid + 1
        elif arr[mid] > target:
            high = mid - 1
        else:
            return mid  # Target found
    return -1  # Target not found

def analyze_search_performance():
    sizes = [1000, 10000, 100000, 1000000]
    
    for size in sizes:
        # Create a sorted list of integers
        sorted_list = list(range(size))
        
        # Best Case: Target is the middle element
        target_best = sorted_list[size // 2]
        start_time = time.time()
        binary_search(sorted_list, target_best)
        best_time = time.time() - start_time

        # Worst Case: Target is greater than the largest element
        target_worst = size + 1
        start_time = time.time()
        binary_search(sorted_list, target_worst)
        worst_time = time.time() - start_time

        # Average Case: Random target
        target_average = random.choice(sorted_list)
        start_time = time.time()
        binary_search(sorted_list, target_average)
        average_time = time.time() - start_time
        
        print(f"Size: {size} -> Best: {best_time:.10f}s, Worst: {worst_time:.10f}s, Average: {average_time:.10f}s")

if __name__ == "__main__":
    analyze_search_performance()
