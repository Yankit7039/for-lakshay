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
 * Problem: Count triplets (i,j,k) where i < j < k and (arr[i] + arr[j] + arr[k]) % d == 0
 * 
 * Constraints:
 * - 3 ≤ n ≤ 10^3
 * - 1 ≤ arr[i] ≤ 10^9
 * - 2 ≤ d ≤ 10^6
 */

int getTripletCount(vector<int> arr, int d) {
    int n = arr.size();
    
    // Handle edge cases (though constraints guarantee n >= 3 and d >= 2)
    if (n < 3) return 0;
    
    int count = 0;
    
    // Iterate through all possible triplets where i < j < k
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                // Use long long to prevent integer overflow
                // Maximum sum: 3 * 10^9 = 3,000,000,000 (well within long long range)
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

int main() {
    // Example from the problem
    vector<int> arr = {3, 3, 4, 7, 8};
    int d = 5;
    
    cout << getTripletCount(arr, d) << endl;
    
    return 0;
}