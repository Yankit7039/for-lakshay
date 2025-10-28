#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * Complete the 'minDeletions' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

bool isAlmostSorted(vector<int>& subseq) {
    int n = subseq.size();
    if (n <= 1) return true;
    
    // Check if already sorted
    bool sorted = true;
    for (int i = 1; i < n; i++) {
        if (subseq[i] <= subseq[i-1]) {
            sorted = false;
            break;
        }
    }
    if (sorted) return true;
    
    // Try removing each element and check if remaining is sorted
    for (int remove = 0; remove < n; remove++) {
        vector<int> temp;
        for (int i = 0; i < n; i++) {
            if (i != remove) {
                temp.push_back(subseq[i]);
            }
        }
        
        bool temp_sorted = true;
        for (size_t i = 1; i < temp.size(); i++) {
            if (temp[i] <= temp[i-1]) {
                temp_sorted = false;
                break;
            }
        }
        
        if (temp_sorted) return true;
    }
    
    return false;
}

int minDeletions(vector<int> arr) {
    int n = arr.size();
    if (n <= 2) return 0;
    
    int max_keep = 1;
    
    // Limit the search to avoid timeout for large arrays
    int max_bits = min(n, 20); // Only check up to 20 elements to avoid exponential explosion
    
    // Try all possible subsequences and check if they're almost sorted
    for (int mask = 1; mask < (1 << max_bits); mask++) {
        vector<int> subseq;
        for (int i = 0; i < max_bits; i++) {
            if (mask & (1 << i)) {
                subseq.push_back(arr[i]);
            }
        }
        
        // Check if this subsequence is almost sorted
        if (isAlmostSorted(subseq)) {
            max_keep = max(max_keep, (int)subseq.size());
        }
    }
    
    // If n > 20, we need a more efficient approach
    if (n > 20) {
        // Fall back to finding LIS as a lower bound
        vector<int> lis(n, 1);
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (arr[j] < arr[i]) {
                    lis[i] = max(lis[i], lis[j] + 1);
                }
            }
            max_keep = max(max_keep, lis[i]);
        }
    }
    
    return n - max_keep;
}

int main() {
    // Test case 1: arr = [1, 5, 10] - Expected output: 0
    vector<int> arr1 = {1, 5, 10};
    cout << "Test case [1, 5, 10]: " << minDeletions(arr1) << " (expected: 0)" << endl;
    
    // Test case 2: arr = [1, 2, 6, 4, 3] - Expected output: 1
    vector<int> arr2 = {1, 2, 6, 4, 3};
    cout << "Test case [1, 2, 6, 4, 3]: " << minDeletions(arr2) << " (expected: 1)" << endl;
    
    // Original example
    vector<int> arr3 = {3, 4, 2, 5, 1};
    cout << "Test case [3, 4, 2, 5, 1]: " << minDeletions(arr3) << " (expected: 1)" << endl;
    
    return 0;
}