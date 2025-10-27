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
