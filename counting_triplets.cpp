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
    int count = 0;
    
    // Check all possible triplets (i, j, k) where i < j < k
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                // Check if sum is divisible by d
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
    
    cout << "Array: [";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i < arr.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    cout << "d = " << d << endl;
    
    int result = getTripletCount(arr, d);
    cout << "Number of triplets: " << result << endl;
    
    // Show the actual triplets for verification
    cout << "\nValid triplets:" << endl;
    int n = arr.size();
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                if ((arr[i] + arr[j] + arr[k]) % d == 0) {
                    cout << "(" << i << ", " << j << ", " << k << "): " 
                         << arr[i] << " + " << arr[j] << " + " << arr[k] 
                         << " = " << (arr[i] + arr[j] + arr[k]) 
                         << " (divisible by " << d << ")" << endl;
                }
            }
        }
    }
    
    return 0;
}