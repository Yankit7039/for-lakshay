#include <bits/stdc++.h>
using namespace std;

/*
 * Complete the 'getTripletCount' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY arr
 *  2. INTEGER d
 * 
 * Constraints:
 * - 3 ≤ n ≤ 10^3
 * - 1 ≤ arr[i] ≤ 10^9  
 * - 2 ≤ d ≤ 10^6
 */

int getTripletCount(vector<int> arr, int d) {
    int n = arr.size();
    
    // Handle edge cases
    if (n < 3) return 0;
    if (d <= 0) return 0;
    
    int count = 0;
    
    // Check all possible triplets (i, j, k) where i < j < k
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                // Use long long to prevent overflow for large numbers
                long long sum = (long long)arr[i] + (long long)arr[j] + (long long)arr[k];
                
                // Check if sum is divisible by d
                if (sum % d == 0) {
                    count++;
                }
            }
        }
    }
    
    return count;
}

// Alternative optimized approach using modular arithmetic
int getTripletCountOptimized(vector<int> arr, int d) {
    int n = arr.size();
    
    // Handle edge cases
    if (n < 3) return 0;
    if (d <= 0) return 0;
    
    int count = 0;
    
    // For each pair (i,j), find k values that make sum divisible by d
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            // Calculate what remainder we need for the third element
            long long pairSum = (long long)arr[i] + (long long)arr[j];
            int pairMod = pairSum % d;
            int needed = (d - pairMod) % d;
            
            // Count elements after position j that have the needed remainder
            for (int k = j + 1; k < n; k++) {
                if (arr[k] % d == needed) {
                    count++;
                }
            }
        }
    }
    
    return count;
}

// Test function to validate different approaches
void testSolution() {
    // Test case 1: Given example
    vector<int> test1 = {3, 3, 4, 7, 8};
    int d1 = 5;
    cout << "Test 1: [3,3,4,7,8], d=5" << endl;
    cout << "Result: " << getTripletCount(test1, d1) << endl;
    cout << "Expected: 3" << endl << endl;
    
    // Test case 2: All same numbers
    vector<int> test2 = {1, 1, 1, 1, 1};
    int d2 = 3;
    cout << "Test 2: [1,1,1,1,1], d=3" << endl;
    cout << "Result: " << getTripletCount(test2, d2) << endl;
    
    // Test case 3: No valid triplets
    vector<int> test3 = {1, 2, 4};
    int d3 = 5;
    cout << "Test 3: [1,2,4], d=5" << endl;
    cout << "Result: " << getTripletCount(test3, d3) << endl;
    cout << "Expected: 0" << endl << endl;
    
    // Test case 4: Large numbers (potential overflow)
    vector<int> test4 = {1000000000, 1000000000, 1000000000};
    int d4 = 1000000;
    cout << "Test 4: [10^9,10^9,10^9], d=10^6" << endl;
    cout << "Result: " << getTripletCount(test4, d4) << endl;
    
    // Test case 5: Minimum size
    vector<int> test5 = {2, 4, 6};
    int d5 = 2;
    cout << "Test 5: [2,4,6], d=2" << endl;
    cout << "Result: " << getTripletCount(test5, d5) << endl;
    cout << "Expected: 1 (2+4+6=12, divisible by 2)" << endl << endl;
    
    // Test case 6: Edge case with d=1 (all sums divisible)
    vector<int> test6 = {1, 2, 3, 4};
    int d6 = 1;
    cout << "Test 6: [1,2,3,4], d=1" << endl;
    cout << "Result: " << getTripletCount(test6, d6) << endl;
    cout << "Expected: 4 (all triplets)" << endl << endl;
    
    // Test case 7: Negative remainders handling
    vector<int> test7 = {1, 5, 9, 13};
    int d7 = 4;
    cout << "Test 7: [1,5,9,13], d=4" << endl;
    cout << "Result: " << getTripletCount(test7, d7) << endl;
}

int main() {
    testSolution();
    return 0;
}