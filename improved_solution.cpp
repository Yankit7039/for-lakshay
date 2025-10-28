#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int minDeletions(vector<int> arr) {
    int n = arr.size();
    if (n <= 2) return 0;
    
    int max_keep = 1;
    
    // Case 1: Find LIS (already sorted subsequences)
    vector<int> lis_ending(n, 1);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                lis_ending[i] = max(lis_ending[i], lis_ending[j] + 1);
            }
        }
        max_keep = max(max_keep, lis_ending[i]);
    }
    
    // Case 2: Find longest subsequence that becomes sorted after removing one element
    // Key insight: such a subsequence has the form: 
    // [increasing part] + [one bad element] + [increasing part]
    // where the bad element can be removed to make it sorted
    
    // Precompute LIS starting from each position
    vector<int> lis_starting(n, 1);
    for (int i = n - 2; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] < arr[j]) {
                lis_starting[i] = max(lis_starting[i], lis_starting[j] + 1);
            }
        }
    }
    
    // For each position i, consider it as the "bad" element to remove
    // Then try to connect the best LIS ending before i with the best LIS starting after i
    for (int bad = 0; bad < n; bad++) {
        // Find best LIS ending before position 'bad'
        int best_before = 0;
        for (int i = 0; i < bad; i++) {
            best_before = max(best_before, lis_ending[i]);
        }
        
        // Find best LIS starting after position 'bad'
        int best_after = 0;
        for (int i = bad + 1; i < n; i++) {
            best_after = max(best_after, lis_starting[i]);
        }
        
        // Also try to connect elements before 'bad' with elements after 'bad'
        int connected = 0;
        for (int i = 0; i < bad; i++) {
            for (int j = bad + 1; j < n; j++) {
                if (arr[i] < arr[j]) {
                    connected = max(connected, lis_ending[i] + lis_starting[j]);
                }
            }
        }
        
        int keep_without_bad = max({best_before, best_after, connected});
        max_keep = max(max_keep, keep_without_bad);
    }
    
    // Additional case: sequences with exactly one "dip" that can be fixed
    // Look for patterns like: ... a[i] > a[j] ... where i < j
    // and see if removing either a[i] or a[j] creates a longer sorted sequence
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] <= arr[j]) continue; // No violation
            
            // Found violation: arr[i] > arr[j]
            // Option 1: Remove arr[i], keep arr[j] and try to extend
            int option1 = 1; // At least keep arr[j]
            
            // Find longest increasing sequence ending before i that can connect to j
            for (int k = 0; k < i; k++) {
                if (arr[k] < arr[j]) {
                    option1 = max(option1, lis_ending[k] + 1);
                }
            }
            
            // Add the longest increasing sequence starting from j
            option1 = max(option1, lis_starting[j]);
            
            // Option 2: Remove arr[j], keep arr[i] and try to extend
            int option2 = lis_ending[i]; // LIS ending at i
            
            // Try to connect arr[i] with elements after j
            for (int k = j + 1; k < n; k++) {
                if (arr[i] < arr[k]) {
                    option2 = max(option2, lis_ending[i] + lis_starting[k]);
                }
            }
            
            max_keep = max(max_keep, max(option1, option2));
        }
    }
    
    return n - max_keep;
}

int main() {
    // Test cases
    vector<int> arr1 = {4};
    cout << minDeletions(arr1) << endl; // 0
    
    vector<int> arr2 = {1, 5, 10};
    cout << minDeletions(arr2) << endl; // 0
    
    vector<int> arr3 = {1, 2, 6, 4, 3};
    cout << minDeletions(arr3) << endl; // 1
    
    vector<int> arr4 = {3, 4, 2, 5, 1};
    cout << minDeletions(arr4) << endl; // 1
    
    // Additional test cases
    vector<int> arr5 = {5, 4, 3, 2, 1};
    cout << minDeletions(arr5) << endl; // Should be 4 (keep only 1 element)
    
    vector<int> arr6 = {1, 3, 2, 4, 5};
    cout << minDeletions(arr6) << endl; // Should be 0 (remove 3 to get [1,2,4,5] which is sorted)
    
    return 0;
}