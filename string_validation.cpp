#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
private:
    unordered_map<string, bool> memo;
    
    string encodeState(const string& s, const vector<int>& counts) {
        string key = s + "|";
        for (int count : counts) {
            key += to_string(count) + ",";
        }
        return key;
    }
    
    bool canFormHelper(const string& s, vector<int>& counts) {
        if (s.empty()) return true;
        
        string key = encodeState(s, counts);
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }
        
        vector<string> words = {"A", "B", "AB", "BA"};
        
        for (int i = 0; i < 4; i++) {
            if (counts[i] > 0 && s.substr(0, words[i].length()) == words[i]) {
                counts[i]--;
                if (canFormHelper(s.substr(words[i].length()), counts)) {
                    counts[i]++;
                    memo[key] = true;
                    return true;
                }
                counts[i]++;
            }
        }
        
        memo[key] = false;
        return false;
    }
    
public:
    int canFormString(string s, vector<int> counts) {
        memo.clear();
        return canFormHelper(s, counts) ? 1 : 0;
    }
};

int main() {
    Solution solution;
    
    // Test cases from the problem
    cout << "Testing string validation solution:\n\n";
    
    // Example 1: s = "B", counts = [1,0,0,0]
    string s1 = "B";
    vector<int> counts1 = {1, 0, 0, 0};
    int result1 = solution.canFormString(s1, counts1);
    cout << "Example 1: s = \"" << s1 << "\", counts = [1,0,0,0]\n";
    cout << "Result: " << result1 << " (Expected: 0)\n";
    cout << "Explanation: We have 1 'A' but need 'B', so impossible\n\n";
    
    // Example 2: s = "ABAB", counts = [1,1,0,1]
    string s2 = "ABAB";
    vector<int> counts2 = {1, 1, 0, 1};
    int result2 = solution.canFormString(s2, counts2);
    cout << "Example 2: s = \"" << s2 << "\", counts = [1,1,0,1]\n";
    cout << "Result: " << result2 << " (Expected: 1)\n";
    cout << "Explanation: Can form as A + B + AB (using 1 A, 1 B, 0 AB, 1 BA -> wait, that's A+B+BA)\n";
    cout << "Actually: A + B + AB is not possible since we have 0 AB\n";
    cout << "But we can do: A + BA + B = A + BA + B = ABAB ✓\n\n";
    
    // Additional test cases
    cout << "Additional test cases:\n";
    
    // Empty string
    int result3 = solution.canFormString("", {0, 0, 0, 0});
    cout << "Empty string: " << result3 << " (Expected: 1)\n";
    
    // Simple cases
    int result4 = solution.canFormString("A", {1, 0, 0, 0});
    cout << "'A' with [1,0,0,0]: " << result4 << " (Expected: 1)\n";
    
    int result5 = solution.canFormString("AB", {0, 0, 1, 0});
    cout << "'AB' with [0,0,1,0]: " << result5 << " (Expected: 1)\n";
    
    int result6 = solution.canFormString("AB", {1, 1, 0, 0});
    cout << "'AB' with [1,1,0,0]: " << result6 << " (Expected: 1)\n";
    
    return 0;
}