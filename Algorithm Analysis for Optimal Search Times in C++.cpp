#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <numeric>
using namespace std;
using namespace std::chrono;

int binary_search(const vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] < target) {
            low = mid + 1;
        } else if (arr[mid] > target) {
            high = mid - 1;
        } else {
            return mid; // Target found
        }
    }
    return -1; // Target not found
}

void analyzeSearchPerformance() {
    vector<int> sizes = {1000, 10000, 100000, 1000000};
    
    for (int size : sizes) {
        vector<int> sorted_list(size);
        // Fill the sorted list with integers
        iota(sorted_list.begin(), sorted_list.end(), 0); // Fill with 0, 1, 2, ..., size-1
        
        // Best Case: Target is the middle element
        int target_best = sorted_list[size / 2];
        auto start = high_resolution_clock::now();
        binary_search(sorted_list, target_best);
        auto best_time = duration_cast<nanoseconds>(high_resolution_clock::now() - start).count();

        // Worst Case: Target is greater than the largest element
        int target_worst = size + 1;
        start = high_resolution_clock::now();
        binary_search(sorted_list, target_worst);
        auto worst_time = duration_cast<nanoseconds>(high_resolution_clock::now() - start).count();

        // Average Case: Random target
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distr(0, size - 1);
        int target_average = sorted_list[distr(gen)];
        start = high_resolution_clock::now();
        binary_search(sorted_list, target_average);
        auto average_time = duration_cast<nanoseconds>(high_resolution_clock::now() - start).count();
        
        cout << "Size: " << size << " -> Best: " << best_time * 1e-9 << "s, "
             << "Worst: " << worst_time * 1e-9 << "s, "
             << "Average: " << average_time * 1e-9 << "s" << endl;
    }
}

int main() {
    analyzeSearchPerformance();
    return 0;
}
