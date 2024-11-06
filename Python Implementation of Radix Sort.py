from typing import List

def counting_sort(arr: List[int], exp: int) -> List[int]:
    n = len(arr)
    output = [0] * n  # Output array
    count = [0] * 10  # Count array for digits (0-9)

    # Count occurrences of each digit
    for i in range(n):
        index = arr[i] // exp
        count[index % 10] += 1

    # Change count[i] so that it contains the actual position of this digit in output[]
    for i in range(1, 10):
        count[i] += count[i - 1]

    # Build the output array
    for i in range(n - 1, -1, -1):
        index = arr[i] // exp
        output[count[index % 10] - 1] = arr[i]
        count[index % 10] -= 1

    return output

def radix_sort(arr: List[int]) -> List[int]:
    # Find the maximum number to determine the number of digits
    max_num = max(arr)

    # Apply counting sort for each digit
    exp = 1  # 10^0
    while max_num // exp > 0:
        arr = counting_sort(arr, exp)
        exp *= 10  # Move to the next digit

    return arr

# Example usage:
product_ids = [1700, 1500, 9999, 1234, 4321]
sorted_ids = radix_sort(product_ids)
print(sorted_ids)
