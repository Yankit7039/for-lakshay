#include <bits/stdc++.h>
using namespace std;

/*
 * Complete the 'getTripletCount' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY arr
 *  2. INTEGER d
 */

int getTripletCount(vector<int> arr, int d) {
    int n = arr.size();
    
    // Handle edge cases
    if (n < 3 || d <= 0) {
        return 0;
    }
    
    int count = 0;
    
    // Check all possible triplets (i, j, k) where i < j < k
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                // Use long long to prevent overflow
                // arr[i] can be up to 10^9, so sum can be up to 3*10^9
                long long sum = (long long)arr[i] + (long long)arr[j] + (long long)arr[k];
                
                // Check if sum is divisible by d
                if (sum % (long long)d == 0) {
                    count++;
                }
            }
        }
    }
    
    return count;
}

int main() {
    // Test with the original example to verify correctness
    vector<int> arr = {3, 3, 4, 7, 8};
    int d = 5;
    
    int result = getTripletCount(arr, d);
    cout << "Result: " << result << endl;
    
    return 0;
}