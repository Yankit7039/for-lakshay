#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<int> solve(vector<int>& A) {
        int N = A.size();
        vector<int> power_array(20, 0);
        
        // For each bit position from most significant (bit 19) to least significant (bit 0)
        for (int i = 0; i < 20; i++) {
            int bit_value = 1 << (19 - i);  // 2^(20-i-1)
            
            // Count elements that have this bit set
            int count = 0;
            for (int num : A) {
                if (num & bit_value) {
                    count++;
                }
            }
            power_array[i] = count;
        }
        
        return power_array;
    }
    
    // Alternative implementation that shows the actual permutation construction
    vector<int> solveWithPermutation(vector<int>& A) {
        int N = A.size();
        vector<int> power_array(20, 0);
        vector<int> remaining = A;
        vector<int> permutation;
        
        // For each bit position from most significant to least significant
        for (int i = 0; i < 20; i++) {
            int bit_value = 1 << (19 - i);  // 2^(20-i-1)
            
            vector<int> with_bit, without_bit;
            
            // Separate elements based on whether they have this bit set
            for (int num : remaining) {
                if (num & bit_value) {
                    with_bit.push_back(num);
                } else {
                    without_bit.push_back(num);
                }
            }
            
            // Add elements with bit set to permutation first
            for (int num : with_bit) {
                permutation.push_back(num);
            }
            
            // Power array value is the count of elements with this bit set
            power_array[i] = with_bit.size();
            
            // Continue with remaining elements
            remaining = without_bit;
        }
        
        // Add any remaining elements
        for (int num : remaining) {
            permutation.push_back(num);
        }
        
        return power_array;
    }
};

// Test function
void test() {
    Solution solution;
    
    // Test case 1
    vector<int> A1 = {1, 2, 3, 4};
    vector<int> result1 = solution.solve(A1);
    cout << "Test 1: A = [1, 2, 3, 4]" << endl;
    cout << "Power array: [";
    for (int i = 0; i < result1.size(); i++) {
        cout << result1[i];
        if (i < result1.size() - 1) cout << ", ";
    }
    cout << "]" << endl << endl;
    
    // Test case 2
    vector<int> A2 = {7, 7, 7, 7};
    vector<int> result2 = solution.solve(A2);
    cout << "Test 2: A = [7, 7, 7, 7]" << endl;
    cout << "Power array: [";
    for (int i = 0; i < result2.size(); i++) {
        cout << result2[i];
        if (i < result2.size() - 1) cout << ", ";
    }
    cout << "]" << endl << endl;
    
    // Test case 3
    vector<int> A3 = {1048575, 524287, 262143};
    vector<int> result3 = solution.solve(A3);
    cout << "Test 3: A = [1048575, 524287, 262143]" << endl;
    cout << "Power array: [";
    for (int i = 0; i < result3.size(); i++) {
        cout << result3[i];
        if (i < result3.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    test();
    return 0;
}