#include <bits/stdc++.h>
using namespace std;

/*
 * Complete the 'minDeletions' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

int minDeletions(vector<int> arr) {
    int n = arr.size();
    if (n <= 2) return 0;
    
    int max_keep = 1;
    
    // Case 1: Longest Increasing Subsequence (already sorted)
    vector<int> lis(n, 1);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                lis[i] = max(lis[i], lis[j] + 1);
            }
        }
        max_keep = max(max_keep, lis[i]);
    }
    
    // Case 2: Subsequence that becomes sorted after removing one element
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] <= arr[j]) continue;
            
            // Found violation: arr[i] > arr[j]
            // Try removing arr[i]: connect elements before i with elements from j onwards
            int keep_without_i = 1; // At least keep arr[j]
            for (int k = 0; k < i; k++) {
                if (arr[k] < arr[j]) {
                    keep_without_i = max(keep_without_i, lis[k] + 1);
                }
            }
            
            // Calculate LIS starting from j
            vector<int> lis_from_j(n, 1);
            for (int k = j + 1; k < n; k++) {
                for (int l = j; l < k; l++) {
                    if (arr[l] < arr[k]) {
                        lis_from_j[k] = max(lis_from_j[k], lis_from_j[l] + 1);
                    }
                }
            }
            
            int max_from_j = 1;
            for (int k = j; k < n; k++) {
                max_from_j = max(max_from_j, lis_from_j[k]);
            }
            
            keep_without_i = max(keep_without_i, max_from_j);
            
            // Try removing arr[j]: connect LIS ending at i with elements after j
            int keep_without_j = lis[i];
            for (int k = j + 1; k < n; k++) {
                if (arr[i] < arr[k]) {
                    keep_without_j = max(keep_without_j, lis[i] + lis_from_j[k]);
                }
            }
            
            max_keep = max(max_keep, max(keep_without_i, keep_without_j));
        }
    }
    
    return n - max_keep;
}

int main() {
    // Example usage
    vector<int> arr = {3, 4, 2, 5, 1};
    cout << minDeletions(arr) << endl; // Should output 1
    return 0;
}