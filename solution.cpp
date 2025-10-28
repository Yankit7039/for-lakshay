#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int validateString(string s, vector<int> counts) {
        // counts[0] = count of A
        // counts[1] = count of B
        // counts[2] = count of AB
        // counts[3] = count of BA
        
        vector<int> currentCounts(4, 0);
        return backtrack(s, 0, counts, currentCounts) ? 1 : 0;
    }
    
private:
    bool backtrack(const string& s, int pos, const vector<int>& targetCounts, vector<int>& currentCounts) {
        // Base case: reached end of string
        if (pos == s.length()) {
            // Check if current counts match target counts
            return currentCounts == targetCounts;
        }
        
        // Try matching word "A"
        if (pos < s.length() && s[pos] == 'A') {
            if (currentCounts[0] < targetCounts[0]) {
                currentCounts[0]++;
                if (backtrack(s, pos + 1, targetCounts, currentCounts)) {
                    return true;
                }
                currentCounts[0]--;
            }
        }
        
        // Try matching word "B"
        if (pos < s.length() && s[pos] == 'B') {
            if (currentCounts[1] < targetCounts[1]) {
                currentCounts[1]++;
                if (backtrack(s, pos + 1, targetCounts, currentCounts)) {
                    return true;
                }
                currentCounts[1]--;
            }
        }
        
        // Try matching word "AB"
        if (pos + 1 < s.length() && s.substr(pos, 2) == "AB") {
            if (currentCounts[2] < targetCounts[2]) {
                currentCounts[2]++;
                if (backtrack(s, pos + 2, targetCounts, currentCounts)) {
                    return true;
                }
                currentCounts[2]--;
            }
        }
        
        // Try matching word "BA"
        if (pos + 1 < s.length() && s.substr(pos, 2) == "BA") {
            if (currentCounts[3] < targetCounts[3]) {
                currentCounts[3]++;
                if (backtrack(s, pos + 2, targetCounts, currentCounts)) {
                    return true;
                }
                currentCounts[3]--;
            }
        }
        
        return false;
    }
};

// Test function
int main() {
    Solution solution;
    
    // Test case 1: s = "B", counts = [1,0,0,0]
    string s1 = "B";
    vector<int> counts1 = {1, 0, 0, 0};
    cout << "Test 1: s = \"B\", counts = [1,0,0,0]" << endl;
    cout << "Result: " << solution.validateString(s1, counts1) << " (Expected: 0)" << endl << endl;
    
    // Test case 2: s = "ABAB", counts = [1,1,0,1]
    string s2 = "ABAB";
    vector<int> counts2 = {1, 1, 0, 1};
    cout << "Test 2: s = \"ABAB\", counts = [1,1,0,1]" << endl;
    cout << "Result: " << solution.validateString(s2, counts2) << " (Expected: 1)" << endl << endl;
    
    // Additional test case 3: s = "AB", counts = [0,0,1,0]
    string s3 = "AB";
    vector<int> counts3 = {0, 0, 1, 0};
    cout << "Test 3: s = \"AB\", counts = [0,0,1,0]" << endl;
    cout << "Result: " << solution.validateString(s3, counts3) << " (Expected: 1)" << endl << endl;
    
    // Additional test case 4: s = "ABBA", counts = [1,1,1,0]
    string s4 = "ABBA";
    vector<int> counts4 = {1, 1, 1, 0};
    cout << "Test 4: s = \"ABBA\", counts = [1,1,1,0]" << endl;
    cout << "Result: " << solution.validateString(s4, counts4) << " (Expected: 1)" << endl << endl;
    
    return 0;
}
