#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Solution {
public:
    map<string, int> memo;
    
    // Helper function to create a state key for memoization
    string getKey(int pos, int a, int b, int ab, int ba) {
        return to_string(pos) + "," + to_string(a) + "," + to_string(b) + "," + to_string(ab) + "," + to_string(ba);
    }
    
    // Recursive function with memoization
    bool canForm(string& s, int pos, int a, int b, int ab, int ba, vector<int>& counts) {
        // Base case: reached end of string
        if (pos == s.length()) {
            // Check if we've used exactly the required counts
            return (a == counts[0] && b == counts[1] && ab == counts[2] && ba == counts[3]);
        }
        
        // Create state key for memoization
        string key = getKey(pos, a, b, ab, ba);
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }
        
        bool result = false;
        
        // Try matching word "A" at current position
        if (pos < s.length() && s[pos] == 'A' && a < counts[0]) {
            result = result || canForm(s, pos + 1, a + 1, b, ab, ba, counts);
        }
        
        // Try matching word "B" at current position
        if (pos < s.length() && s[pos] == 'B' && b < counts[1]) {
            result = result || canForm(s, pos + 1, a, b + 1, ab, ba, counts);
        }
        
        // Try matching word "AB" at current position
        if (pos + 1 < s.length() && s[pos] == 'A' && s[pos + 1] == 'B' && ab < counts[2]) {
            result = result || canForm(s, pos + 2, a, b, ab + 1, ba, counts);
        }
        
        // Try matching word "BA" at current position
        if (pos + 1 < s.length() && s[pos] == 'B' && s[pos + 1] == 'A' && ba < counts[3]) {
            result = result || canForm(s, pos + 2, a, b, ab, ba + 1, counts);
        }
        
        memo[key] = result;
        return result;
    }
    
    int isValid(string s, vector<int>& counts) {
        memo.clear();
        return canForm(s, 0, 0, 0, 0, 0, counts) ? 1 : 0;
    }
};

int main() {
    Solution sol;
    
    // Test case 1: s = "B", counts = [1,0,0,0]
    string s1 = "B";
    vector<int> counts1 = {1, 0, 0, 0};
    cout << "Test 1: s = \"" << s1 << "\", counts = [1,0,0,0]" << endl;
    cout << "Result: " << sol.isValid(s1, counts1) << " (Expected: 0)" << endl << endl;
    
    // Test case 2: s = "ABAB", counts = [1,1,0,1]
    string s2 = "ABAB";
    vector<int> counts2 = {1, 1, 0, 1};
    cout << "Test 2: s = \"" << s2 << "\", counts = [1,1,0,1]" << endl;
    cout << "Result: " << sol.isValid(s2, counts2) << " (Expected: 1)" << endl << endl;
    
    // Additional test case 3: s = "A", counts = [1,0,0,0]
    string s3 = "A";
    vector<int> counts3 = {1, 0, 0, 0};
    cout << "Test 3: s = \"" << s3 << "\", counts = [1,0,0,0]" << endl;
    cout << "Result: " << sol.isValid(s3, counts3) << " (Expected: 1)" << endl << endl;
    
    // Additional test case 4: s = "AB", counts = [0,0,1,0]
    string s4 = "AB";
    vector<int> counts4 = {0, 0, 1, 0};
    cout << "Test 4: s = \"" << s4 << "\", counts = [0,0,1,0]" << endl;
    cout << "Result: " << sol.isValid(s4, counts4) << " (Expected: 1)" << endl << endl;
    
    // Additional test case 5: s = "AABB", counts = [2,2,0,0]
    string s5 = "AABB";
    vector<int> counts5 = {2, 2, 0, 0};
    cout << "Test 5: s = \"" << s5 << "\", counts = [2,2,0,0]" << endl;
    cout << "Result: " << sol.isValid(s5, counts5) << " (Expected: 1)" << endl << endl;
    
    return 0;
}
