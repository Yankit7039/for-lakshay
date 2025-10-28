#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int minDeletions(vector<int> arr) {
    int n = arr.size();
    if (n <= 2) return 0;
    
    // The key insight: we want the longest subsequence that is "almost sorted"
    // Almost sorted = can be made sorted by removing at most 1 element
    
    int max_keep = 1;
    
    // Method: For each possible subsequence, check if it's almost sorted
    // But we need to be efficient, so we'll use a different approach
    
    // First, find all LIS (these are already sorted, so almost sorted)
    vector<int> lis(n, 1);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                lis[i] = max(lis[i], lis[j] + 1);
            }
        }
        max_keep = max(max_keep, lis[i]);
    }
    
    // Second, for each element, try removing it and find LIS of remaining array
    // If LIS of remaining array is L, then original subsequence of length L+1 
    // can be made sorted by removing 1 element
    
    for (int skip = 0; skip < n; skip++) {
        // Build array without element at position 'skip'
        vector<int> remaining;
        vector<int> original_indices;
        
        for (int i = 0; i < n; i++) {
            if (i != skip) {
                remaining.push_back(arr[i]);
                original_indices.push_back(i);
            }
        }
        
        if (remaining.empty()) continue;
        
        // Find LIS of remaining array
        int m = remaining.size();
        vector<int> dp(m, 1);
        
        for (int i = 1; i < m; i++) {
            for (int j = 0; j < i; j++) {
                if (remaining[j] < remaining[i]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        
        int max_lis_remaining = 1;
        for (int i = 0; i < m; i++) {
            max_lis_remaining = max(max_lis_remaining, dp[i]);
        }
        
        // This means we can keep max_lis_remaining elements from the remaining array
        // These form a sorted subsequence, so they're almost sorted
        max_keep = max(max_keep, max_lis_remaining);
    }
    
    // Third, try to find sequences that have exactly one "bad" element
    // that when removed, the rest forms an increasing sequence
    
    // For efficiency with larger inputs, we'll also try a greedy approach
    // Try to build longest increasing subsequence, but allow one "mistake"
    
    for (int start = 0; start < n; start++) {
        // Try building an almost-sorted sequence starting from position 'start'
        vector<int> seq;
        seq.push_back(arr[start]);
        bool used_mistake = false;
        
        for (int i = start + 1; i < n; i++) {
            if (seq.empty() || arr[i] > seq.back()) {
                // Can add this element
                seq.push_back(arr[i]);
            } else if (!used_mistake) {
                // Use our one mistake - skip this element
                used_mistake = true;
            }
            // If we already used our mistake and this element doesn't fit, skip it
        }
        
        max_keep = max(max_keep, (int)seq.size());
        
        // Also try the variant where we remove an element from the sequence we built
        if (seq.size() > 1) {
            for (int remove_idx = 0; remove_idx < seq.size(); remove_idx++) {
                vector<int> temp_seq;
                for (int j = 0; j < seq.size(); j++) {
                    if (j != remove_idx) {
                        temp_seq.push_back(seq[j]);
                    }
                }
                
                // Check if temp_seq is sorted
                bool is_sorted = true;
                for (int j = 1; j < temp_seq.size(); j++) {
                    if (temp_seq[j] <= temp_seq[j-1]) {
                        is_sorted = false;
                        break;
                    }
                }
                
                if (is_sorted) {
                    max_keep = max(max_keep, (int)temp_seq.size());
                }
            }
        }
    }
    
    return n - max_keep;
}

int main() {
    vector<int> test1 = {1, 5, 10};
    cout << minDeletions(test1) << endl;
    
    vector<int> test2 = {1, 2, 6, 4, 3};
    cout << minDeletions(test2) << endl;
    
    vector<int> test3 = {3, 4, 2, 5, 1};
    cout << minDeletions(test3) << endl;
    
    return 0;
}