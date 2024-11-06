#include <vector>
#include <algorithm>
#include <iostream>

void countingSort(std::vector<int>& arr, int exp) {
    int n = arr.size();
    std::vector<int> output(n);
    int count[10] = {0}; // Count array for digits (0-9)

    // Count occurrences of each digit
    for (int i = 0; i < n; i++) {
        int index = arr[i] / exp;
        count[index % 10]++;
    }

    // Change count[i] so that it contains the actual position of this digit in output[]
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        int index = arr[i] / exp;
        output[count[index % 10] - 1] = arr[i];
        count[index % 10]--;
    }

    // Copy the output array back to arr, so that arr now contains sorted numbers
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

std::vector<int> radixSort(std::vector<int>& arr) {
    // Find the maximum number to determine the number of digits
    int max_num = *std::max_element(arr.begin(), arr.end());

    // Apply counting sort for each digit
    for (int exp = 1; max_num / exp > 0; exp *= 10) {
        countingSort(arr, exp);
    }

    return arr;
}

// Example usage:
int main() {
    std::vector<int> product_ids = {1700, 1500, 9999, 1234, 4321};
    radixSort(product_ids);
    for (int id : product_ids) {
        std::cout << id << " ";
    }
    return 0;
}
