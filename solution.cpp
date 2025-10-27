#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int checkValidString(string s, vector<int> counts) {
        // counts[0] = count of "A"
        // counts[1] = count of "B"
        // counts[2] = count of "AB"
        // counts[3] = count of "BA"
        
        vector<int> remaining = counts;
        return backtrack(s, 0, remaining) ? 1 : 0;
    }
    
private:
    bool backtrack(const string& s, int pos, vector<int>& remaining) {
        // Base case: reached end of string
        if (pos == s.length()) {
            // Check if all counts are used up
            return remaining[0] == 0 && remaining[1] == 0 && 
                   remaining[2] == 0 && remaining[3] == 0;
        }
        
        // Try matching single character words first
        if (s[pos] == 'A' && remaining[0] > 0) {
            remaining[0]--;
            if (backtrack(s, pos + 1, remaining)) {
                return true;
            }
            remaining[0]++;
        }
        
        if (s[pos] == 'B' && remaining[1] > 0) {
            remaining[1]--;
            if (backtrack(s, pos + 1, remaining)) {
                return true;
            }
            remaining[1]++;
        }
        
        // Try matching two character words
        if (pos + 1 < s.length()) {
            string twoChar = s.substr(pos, 2);
            
            if (twoChar == "AB" && remaining[2] > 0) {
                remaining[2]--;
                if (backtrack(s, pos + 2, remaining)) {
                    return true;
                }
                remaining[2]++;
            }
            
            if (twoChar == "BA" && remaining[3] > 0) {
                remaining[3]--;
                if (backtrack(s, pos + 2, remaining)) {
                    return true;
                }
                remaining[3]++;
            }
        }
        
        return false;
    }
};

int main() {
    Solution sol;
    
    // Test case 1: s = "B", counts = [1,0,0,0]
    cout << "Test 1: " << sol.checkValidString("B", {1, 0, 0, 0}) << endl;
    // Expected: 0 (because we have count for A but string is B)
    
    // Test case 2: s = "ABAB", counts = [1,1,0,1]
    cout << "Test 2: " << sol.checkValidString("ABAB", {1, 1, 0, 1}) << endl;
    // Expected: 1 (A + BA + B = ABAB)
    
    // Additional test cases
    cout << "Test 3: " << sol.checkValidString("A", {1, 0, 0, 0}) << endl;
    // Expected: 1
    
    cout << "Test 4: " << sol.checkValidString("AB", {0, 0, 1, 0}) << endl;
    // Expected: 1
    
    cout << "Test 5: " << sol.checkValidString("AABB", {2, 2, 0, 0}) << endl;
    // Expected: 1
    
    return 0;
}
