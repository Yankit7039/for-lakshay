#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Check if a sequence is almost sorted (can be made sorted by removing at most 1 element)
bool isAlmostSorted(const vector<int>& seq) {
    int n = seq.size();
    if (n <= 1) return true;
    
    // First check if it's already sorted
    bool already_sorted = true;
    for (int i = 1; i < n; i++) {
        if (seq[i] <= seq[i-1]) {
            already_sorted = false;
            break;
        }
    }
    if (already_sorted) return true;
    
    // Try removing each element and check if the result is sorted
    for (int remove = 0; remove < n; remove++) {
        vector<int> temp;
        for (int i = 0; i < n; i++) {
            if (i != remove) {
                temp.push_back(seq[i]);
            }
        }
        
        // Check if temp is sorted
        bool is_sorted = true;
        for (int i = 1; i < temp.size(); i++) {
            if (temp[i] <= temp[i-1]) {
                is_sorted = false;
                break;
            }
        }
        
        if (is_sorted) return true;
    }
    
    return false;
}

int minDeletions(vector<int> arr) {
    int n = arr.size();
    if (n <= 2) return 0;
    
    int max_keep = 1;
    
    // Try all possible subsequences (for small n) or use heuristics (for large n)
    if (n <= 20) {
        // Brute force for small arrays
        for (int mask = 1; mask < (1 << n); mask++) {
            vector<int> subseq;
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    subseq.push_back(arr[i]);
                }
            }
            
            if (isAlmostSorted(subseq)) {
                max_keep = max(max_keep, (int)subseq.size());
            }
        }
    } else {
        // For larger arrays, use more efficient approach
        // Find LIS first
        vector<int> lis(n, 1);
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (arr[j] < arr[i]) {
                    lis[i] = max(lis[i], lis[j] + 1);
                }
            }
            max_keep = max(max_keep, lis[i]);
        }
        
        // Try removing each element and finding LIS of the rest
        for (int remove = 0; remove < n; remove++) {
            vector<int> temp;
            for (int i = 0; i < n; i++) {
                if (i != remove) {
                    temp.push_back(arr[i]);
                }
            }
            
            if (temp.empty()) continue;
            
            // Find LIS of temp
            int m = temp.size();
            vector<int> temp_lis(m, 1);
            for (int i = 1; i < m; i++) {
                for (int j = 0; j < i; j++) {
                    if (temp[j] < temp[i]) {
                        temp_lis[i] = max(temp_lis[i], temp_lis[j] + 1);
                    }
                }
            }
            
            int max_temp_lis = 1;
            for (int i = 0; i < m; i++) {
                max_temp_lis = max(max_temp_lis, temp_lis[i]);
            }
            
            max_keep = max(max_keep, max_temp_lis);
        }
    }
    
    return n - max_keep;
}

int main() {
    // Test cases
    cout << minDeletions({1, 5, 10}) << endl;      // Expected: 0
    cout << minDeletions({1, 2, 6, 4, 3}) << endl; // Expected: 1  
    cout << minDeletions({3, 4, 2, 5, 1}) << endl; // Expected: 1
    
    return 0;
}