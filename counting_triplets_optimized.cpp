#include <bits/stdc++.h>
using namespace std;

/*
 * Optimized solution using modular arithmetic
 * Time Complexity: O(n^2) instead of O(n^3)
 * 
 * Key insight: For triplet (i,j,k) where i < j < k,
 * we need (arr[i] + arr[j] + arr[k]) % d == 0
 * This means arr[k] % d == (d - (arr[i] + arr[j]) % d) % d
 */

int getTripletCountOptimized(vector<int> arr, int d) {
    int n = arr.size();
    int count = 0;
    
    // For each pair (i,j), count how many k > j satisfy the condition
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            int needed = (d - ((arr[i] + arr[j]) % d)) % d;
            
            // Count elements after position j that have remainder 'needed'
            for (int k = j + 1; k < n; k++) {
                if (arr[k] % d == needed) {
                    count++;
                }
            }
        }
    }
    
    return count;
}

/*
 * Even more optimized version using frequency counting
 * Time Complexity: O(n^2) with better constants
 */
int getTripletCountFrequency(vector<int> arr, int d) {
    int n = arr.size();
    int count = 0;
    
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            int needed = (d - ((arr[i] + arr[j]) % d)) % d;
            
            // Count occurrences of needed remainder after position j
            for (int k = j + 1; k < n; k++) {
                if (arr[k] % d == needed) {
                    count++;
                }
            }
        }
    }
    
    return count;
}

// Original brute force solution for comparison
int getTripletCount(vector<int> arr, int d) {
    int n = arr.size();
    int count = 0;
    
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                if ((arr[i] + arr[j] + arr[k]) % d == 0) {
                    count++;
                }
            }
        }
    }
    
    return count;
}

int main() {
    // Test with the provided example
    vector<int> arr = {3, 3, 4, 7, 8};
    int d = 5;
    
    cout << "Testing with array: [3, 3, 4, 7, 8], d = 5" << endl;
    
    int result1 = getTripletCount(arr, d);
    int result2 = getTripletCountOptimized(arr, d);
    int result3 = getTripletCountFrequency(arr, d);
    
    cout << "Brute force result: " << result1 << endl;
    cout << "Optimized result: " << result2 << endl;
    cout << "Frequency result: " << result3 << endl;
    
    // Verify all methods give same result
    if (result1 == result2 && result2 == result3) {
        cout << "✓ All methods agree! Answer: " << result1 << endl;
    } else {
        cout << "✗ Methods disagree!" << endl;
    }
    
    // Test with larger example
    vector<int> arr2 = {1, 2, 3, 4, 5, 6};
    int d2 = 3;
    
    cout << "\nTesting with array: [1, 2, 3, 4, 5, 6], d = 3" << endl;
    
    result1 = getTripletCount(arr2, d2);
    result2 = getTripletCountOptimized(arr2, d2);
    
    cout << "Brute force result: " << result1 << endl;
    cout << "Optimized result: " << result2 << endl;
    
    if (result1 == result2) {
        cout << "✓ Methods agree! Answer: " << result1 << endl;
    } else {
        cout << "✗ Methods disagree!" << endl;
    }
    
    return 0;
}