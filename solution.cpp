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
    
    // Helper function to check if array is sorted
    auto isSorted = [](const vector<int>& a) -> bool {
        for (int i = 1; i < a.size(); i++) {
            if (a[i] <= a[i-1]) return false;
        }
        return true;
    };
    
    // Helper function to check if array is almost sorted
    // (can remove at most 1 element to make it sorted)
    auto isAlmostSorted = [&](const vector<int>& a) -> bool {
        if (a.size() <= 2) return true;
        if (isSorted(a)) return true;
        
        // Try removing each element
        for (int remove = 0; remove < a.size(); remove++) {
            vector<int> temp;
            for (int i = 0; i < a.size(); i++) {
                if (i != remove) temp.push_back(a[i]);
            }
            if (isSorted(temp)) return true;
        }
        return false;
    };
    
    // Try removing minimum number of elements until we get an almost sorted array
    for (int remove = 0; remove < n; remove++) {
        // For efficiency, use bit manipulation for small arrays
        if (n <= 20) {
            // Try all combinations using bitmask
            for (int mask = 0; mask < (1 << n); mask++) {
                if (__builtin_popcount(mask) != remove) continue;
                
                vector<int> remaining;
                for (int i = 0; i < n; i++) {
                    if (!(mask & (1 << i))) {
                        remaining.push_back(arr[i]);
                    }
                }
                
                if (remaining.empty()) continue;
                
                if (isAlmostSorted(remaining)) {
                    return remove;
                }
            }
        } else {
            // For larger arrays, use next_permutation approach
            vector<bool> toRemove(n, false);
            fill(toRemove.begin(), toRemove.begin() + remove, true);
            
            do {
                vector<int> remaining;
                for (int i = 0; i < n; i++) {
                    if (!toRemove[i]) {
                        remaining.push_back(arr[i]);
                    }
                }
                
                if (remaining.empty()) continue;
                
                if (isAlmostSorted(remaining)) {
                    return remove;
                }
                
            } while (next_permutation(toRemove.begin(), toRemove.end()));
        }
    }
    
    return n; // Worst case: remove all elements
}

int main() {
    // Test cases
    vector<int> test1 = {3, 4, 2, 5};
    cout << "minDeletions([3, 4, 2, 5]) = " << minDeletions(test1) << endl;
    
    vector<int> test2 = {1, 2, 3, 4, 5};
    cout << "minDeletions([1, 2, 3, 4, 5]) = " << minDeletions(test2) << endl;
    
    vector<int> test3 = {5, 4, 3, 2, 1};
    cout << "minDeletions([5, 4, 3, 2, 1]) = " << minDeletions(test3) << endl;
    
    vector<int> test4 = {1, 3, 2, 4};
    cout << "minDeletions([1, 3, 2, 4]) = " << minDeletions(test4) << endl;
    
    return 0;
}