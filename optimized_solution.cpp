#include <bits/stdc++.h>
using namespace std;

/*
 * Optimized solution for getTripletCount
 * Handles edge cases and potential overflow issues
 * 
 * Time Complexity: O(n^3) - unavoidable for this problem
 * Space Complexity: O(1)
 * 
 * Key optimizations:
 * 1. Use long long to prevent overflow
 * 2. Early termination for edge cases
 * 3. Proper modular arithmetic
 */

int getTripletCount(vector<int> arr, int d) {
    int n = arr.size();
    
    // Edge case handling
    if (n < 3) return 0;
    if (d <= 0) return 0;
    
    int count = 0;
    
    // Convert d to long long once to avoid repeated casting
    long long divisor = (long long)d;
    
    // Check all possible triplets (i, j, k) where i < j < k
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                // Calculate sum using long long to handle large values
                // Maximum possible sum: 3 * 10^9 = 3,000,000,000 (fits in long long)
                long long sum = (long long)arr[i] + (long long)arr[j] + (long long)arr[k];
                
                // Check divisibility
                if (sum % divisor == 0) {
                    count++;
                }
            }
        }
    }
    
    return count;
}

// Alternative approach using modular arithmetic (same complexity but different approach)
int getTripletCountMod(vector<int> arr, int d) {
    int n = arr.size();
    
    if (n < 3) return 0;
    if (d <= 0) return 0;
    
    int count = 0;
    
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            // Calculate what remainder the third element needs
            long long pairSum = (long long)arr[i] + (long long)arr[j];
            int pairMod = pairSum % d;
            int needed = (d - pairMod) % d;
            
            // Count elements after j with the needed remainder
            for (int k = j + 1; k < n; k++) {
                if (arr[k] % d == needed) {
                    count++;
                }
            }
        }
    }
    
    return count;
}

int main() {
    // Test cases
    vector<vector<int>> testArrays = {
        {3, 3, 4, 7, 8},           // Original example
        {1, 1, 1},                 // Minimum size
        {1000000000, 1000000000, 1000000000}, // Large numbers
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}       // Larger array
    };
    
    vector<int> testDs = {5, 3, 1000000, 6};
    
    for (int i = 0; i < testArrays.size(); i++) {
        int result1 = getTripletCount(testArrays[i], testDs[i]);
        int result2 = getTripletCountMod(testArrays[i], testDs[i]);
        
        cout << "Test " << (i+1) << ": ";
        cout << "Method1=" << result1 << ", Method2=" << result2;
        if (result1 == result2) {
            cout << " ✓";
        } else {
            cout << " ✗";
        }
        cout << endl;
    }
    
    return 0;
}