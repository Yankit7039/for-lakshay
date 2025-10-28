#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool canFormString(const string& s, int pos, vector<int>& counts, const vector<int>& target) {
    // Base case: reached end of string
    if (pos == s.length()) {
        // Check if all counts match
        return counts[0] == target[0] && counts[1] == target[1] && 
               counts[2] == target[2] && counts[3] == target[3];
    }
    
    // Try matching "AB" (2 chars) - index 2 in counts
    if (pos + 1 < s.length() && s[pos] == 'A' && s[pos + 1] == 'B' && counts[2] < target[2]) {
        counts[2]++;
        if (canFormString(s, pos + 2, counts, target)) return true;
        counts[2]--;
    }
    
    // Try matching "BA" (2 chars) - index 3 in counts
    if (pos + 1 < s.length() && s[pos] == 'B' && s[pos + 1] == 'A' && counts[3] < target[3]) {
        counts[3]++;
        if (canFormString(s, pos + 2, counts, target)) return true;
        counts[3]--;
    }
    
    // Try matching "A" (1 char) - index 0 in counts
    if (s[pos] == 'A' && counts[0] < target[0]) {
        counts[0]++;
        if (canFormString(s, pos + 1, counts, target)) return true;
        counts[0]--;
    }
    
    // Try matching "B" (1 char) - index 1 in counts
    if (s[pos] == 'B' && counts[1] < target[1]) {
        counts[1]++;
        if (canFormString(s, pos + 1, counts, target)) return true;
        counts[1]--;
    }
    
    return false;
}

int solution(string s, vector<int> counts) {
    // counts[0] = count of A
    // counts[1] = count of B
    // counts[2] = count of AB
    // counts[3] = count of BA
    
    vector<int> currentCounts(4, 0);
    
    if (canFormString(s, 0, currentCounts, counts)) {
        return 1;
    }
    return 0;
}

// Test cases
int main() {
    // Test case 1: s = "B", counts = [1, 0, 0, 0]
    // Expected: 0 (B can't be word A)
    cout << "Test 1: " << solution("B", {1, 0, 0, 0}) << " (Expected: 0)" << endl;
    
    // Test case 2: s = "ABAB", counts = [1, 1, 0, 1]
    // Expected: 1 (A + BA + B = ABAB)
    cout << "Test 2: " << solution("ABAB", {1, 1, 0, 1}) << " (Expected: 1)" << endl;
    
    // Test case 3: s = "A", counts = [1, 0, 0, 0]
    // Expected: 1 (A = A)
    cout << "Test 3: " << solution("A", {1, 0, 0, 0}) << " (Expected: 1)" << endl;
    
    // Test case 4: s = "AB", counts = [0, 0, 1, 0]
    // Expected: 1 (AB = AB)
    cout << "Test 4: " << solution("AB", {0, 0, 1, 0}) << " (Expected: 1)" << endl;
    
    // Test case 5: s = "AB", counts = [1, 1, 0, 0]
    // Expected: 1 (A + B = AB)
    cout << "Test 5: " << solution("AB", {1, 1, 0, 0}) << " (Expected: 1)" << endl;
    
    // Test case 6: s = "BABA", counts = [1, 1, 0, 1]
    // Expected: 1 (B + A + BA = BABA or BA + BA = BABA... wait second doesn't work)
    cout << "Test 6: " << solution("BABA", {1, 1, 0, 1}) << " (Expected: 1)" << endl;
    
    return 0;
}
