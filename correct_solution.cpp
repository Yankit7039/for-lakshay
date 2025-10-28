#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int minDeletions(vector<int> arr) {
    int n = arr.size();
    if (n <= 2) return 0;
    
    int max_almost_sorted_length = 1;
    
    // Dynamic programming approach
    // dp[i][0] = length of longest increasing subsequence ending at i
    // dp[i][1] = length of longest "almost sorted" subsequence ending at i
    //            (where we can remove at most 1 element to make it sorted)
    
    vector<int> lis(n, 1); // LIS ending at each position
    
    // Calculate LIS for each position
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                lis[i] = max(lis[i], lis[j] + 1);
            }
        }
        max_almost_sorted_length = max(max_almost_sorted_length, lis[i]);
    }
    
    // Now find longest subsequence that can be made sorted by removing exactly 1 element
    // This means we have at most one "bad" position that breaks the increasing order
    
    // For each pair (i,j) where i < j and arr[i] >= arr[j] (violation)
    // Try to build the longest sequence by either:
    // 1. Removing arr[i] and connecting elements before i with elements from j onwards
    // 2. Removing arr[j] and connecting elements up to i with elements after j
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] < arr[j]) continue; // No violation
            
            // Violation found: arr[i] >= arr[j]
            
            // Option 1: Remove arr[i]
            // Find LIS ending before position i that can connect to position j
            int max_before_i_connecting_to_j = 1; // At least arr[j]
            for (int k = 0; k < i; k++) {
                if (arr[k] < arr[j]) {
                    max_before_i_connecting_to_j = max(max_before_i_connecting_to_j, lis[k] + 1);
                }
            }
            
            // Find LIS starting from position j
            int lis_from_j = 1;
            vector<int> temp_lis(n, 1);
            for (int p = j + 1; p < n; p++) {
                for (int q = j; q < p; q++) {
                    if (arr[q] < arr[p]) {
                        temp_lis[p] = max(temp_lis[p], temp_lis[q] + 1);
                    }
                }
                lis_from_j = max(lis_from_j, temp_lis[p]);
            }
            
            int option1 = max(max_before_i_connecting_to_j, lis_from_j);
            max_almost_sorted_length = max(max_almost_sorted_length, option1);
            
            // Option 2: Remove arr[j]
            // Keep LIS ending at i and try to connect with elements after j
            int option2 = lis[i];
            for (int k = j + 1; k < n; k++) {
                if (arr[i] < arr[k]) {
                    option2 = max(option2, lis[i] + temp_lis[k]);
                }
            }
            max_almost_sorted_length = max(max_almost_sorted_length, option2);
        }
    }
    
    // Also check sequences where we remove one element from the middle
    // and the remaining forms a valid increasing sequence
    for (int remove = 0; remove < n; remove++) {
        // Create array without element at position 'remove'
        vector<int> temp_arr;
        for (int i = 0; i < n; i++) {
            if (i != remove) {
                temp_arr.push_back(arr[i]);
            }
        }
        
        // Find LIS of this array
        if (temp_arr.empty()) continue;
        
        int temp_n = temp_arr.size();
        vector<int> temp_lis(temp_n, 1);
        
        for (int i = 1; i < temp_n; i++) {
            for (int j = 0; j < i; j++) {
                if (temp_arr[j] < temp_arr[i]) {
                    temp_lis[i] = max(temp_lis[i], temp_lis[j] + 1);
                }
            }
        }
        
        int max_lis_without_remove = 1;
        for (int i = 0; i < temp_n; i++) {
            max_lis_without_remove = max(max_lis_without_remove, temp_lis[i]);
        }
        
        max_almost_sorted_length = max(max_almost_sorted_length, max_lis_without_remove);
    }
    
    return n - max_almost_sorted_length;
}

int main() {
    // Test the given examples
    vector<int> test1 = {1, 5, 10};
    cout << minDeletions(test1) << endl; // Expected: 0
    
    vector<int> test2 = {1, 2, 6, 4, 3};
    cout << minDeletions(test2) << endl; // Expected: 1
    
    vector<int> test3 = {3, 4, 2, 5, 1};
    cout << minDeletions(test3) << endl; // Expected: 1
    
    return 0;
}