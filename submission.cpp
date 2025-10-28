#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int minDeletions(vector<int> arr) {
    int n = arr.size();
    if (n <= 2) return 0;
    
    int max_keep = 1;
    
    // For small arrays, use brute force (guaranteed correct)
    if (n <= 18) {
        // Check if a sequence is almost sorted
        auto isAlmostSorted = [](const vector<int>& seq) -> bool {
            int n = seq.size();
            if (n <= 1) return true;
            
            // Check if already sorted
            bool sorted = true;
            for (int i = 1; i < n; i++) {
                if (seq[i] <= seq[i-1]) {
                    sorted = false;
                    break;
                }
            }
            if (sorted) return true;
            
            // Try removing each element
            for (int remove = 0; remove < n; remove++) {
                vector<int> temp;
                for (int i = 0; i < n; i++) {
                    if (i != remove) {
                        temp.push_back(seq[i]);
                    }
                }
                
                bool is_sorted = true;
                for (int i = 1; i < temp.size(); i++) {
                    if (temp[i] <= temp[i-1]) {
                        is_sorted = false;
                        break;
                    }
                }
                
                if (is_sorted) return true;
            }
            return false;
        };
        
        // Try all subsequences
        for (int mask = 1; mask < (1 << n); mask++) {
            vector<int> subseq;
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    subseq.push_back(arr[i]);
                }
            }
            
            if (isAlmostSorted(subseq)) {
                max_keep = max(max_keep, (int)subseq.size());
            }
        }
    } else {
        // For larger arrays, use optimized approach
        
        // 1. Find LIS (these are already sorted, hence almost sorted)
        vector<int> lis(n, 1);
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (arr[j] < arr[i]) {
                    lis[i] = max(lis[i], lis[j] + 1);
                }
            }
            max_keep = max(max_keep, lis[i]);
        }
        
        // 2. For each position, try removing it and find LIS of remaining
        for (int remove = 0; remove < n; remove++) {
            vector<int> temp;
            for (int i = 0; i < n; i++) {
                if (i != remove) {
                    temp.push_back(arr[i]);
                }
            }
            
            if (temp.empty()) continue;
            
            // Find LIS of temp array
            int m = temp.size();
            vector<int> temp_lis(m, 1);
            for (int i = 1; i < m; i++) {
                for (int j = 0; j < i; j++) {
                    if (temp[j] < temp[i]) {
                        temp_lis[i] = max(temp_lis[i], temp_lis[j] + 1);
                    }
                }
            }
            
            int max_temp_lis = 1;
            for (int i = 0; i < m; i++) {
                max_temp_lis = max(max_temp_lis, temp_lis[i]);
            }
            
            max_keep = max(max_keep, max_temp_lis);
        }
        
        // 3. Try to find sequences with exactly one violation that can be fixed
        vector<int> lis_start(n, 1);
        for (int i = n - 2; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {
                if (arr[i] < arr[j]) {
                    lis_start[i] = max(lis_start[i], lis_start[j] + 1);
                }
            }
        }
        
        // For each pair (i,j) where i < j and arr[i] >= arr[j] (violation)
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (arr[i] < arr[j]) continue;
                
                // Found violation: arr[i] >= arr[j]
                // Try removing arr[i] or arr[j]
                
                // Option 1: Remove arr[i], connect before i with from j
                int option1 = lis_start[j];
                for (int k = 0; k < i; k++) {
                    if (arr[k] < arr[j]) {
                        option1 = max(option1, lis[k] + lis_start[j]);
                    }
                }
                
                // Option 2: Remove arr[j], use LIS ending at i and continue after j
                int option2 = lis[i];
                for (int k = j + 1; k < n; k++) {
                    if (arr[i] < arr[k]) {
                        option2 = max(option2, lis[i] + lis_start[k]);
                    }
                }
                
                max_keep = max(max_keep, max(option1, option2));
            }
        }
    }
    
    return n - max_keep;
}