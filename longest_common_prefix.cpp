#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

class LongestCommonPrefix {
public:
    // Method 1: Horizontal scanning (most efficient for typical cases)
    static std::string horizontalScanning(const std::vector<std::string>& strs) {
        if (strs.empty()) return "";
        if (strs.size() == 1) return strs[0];
        
        std::string prefix = strs[0];
        
        for (size_t i = 1; i < strs.size() && !prefix.empty(); ++i) {
            // Early termination if prefix becomes empty
            if (prefix.empty()) break;
            
            // Find minimum length to avoid unnecessary comparisons
            size_t minLen = std::min(prefix.length(), strs[i].length());
            
            // Compare character by character
            size_t j = 0;
            while (j < minLen && prefix[j] == strs[i][j]) {
                ++j;
            }
            
            // Update prefix to the common part
            prefix = prefix.substr(0, j);
        }
        
        return prefix;
    }
    
    // Method 2: Vertical scanning (good for very long strings)
    static std::string verticalScanning(const std::vector<std::string>& strs) {
        if (strs.empty()) return "";
        if (strs.size() == 1) return strs[0];
        
        // Find minimum length to avoid out-of-bounds access
        size_t minLen = strs[0].length();
        for (const auto& str : strs) {
            minLen = std::min(minLen, str.length());
        }
        
        // Compare character by character across all strings
        for (size_t i = 0; i < minLen; ++i) {
            char currentChar = strs[0][i];
            for (size_t j = 1; j < strs.size(); ++j) {
                if (strs[j][i] != currentChar) {
                    return strs[0].substr(0, i);
                }
            }
        }
        
        return strs[0].substr(0, minLen);
    }
    
    // Method 3: Binary search approach (optimal for very long strings with short common prefix)
    static std::string binarySearch(const std::vector<std::string>& strs) {
        if (strs.empty()) return "";
        if (strs.size() == 1) return strs[0];
        
        // Find minimum length
        size_t minLen = strs[0].length();
        for (const auto& str : strs) {
            minLen = std::min(minLen, str.length());
        }
        
        int left = 0, right = minLen;
        
        while (left < right) {
            int mid = left + (right - left + 1) / 2;
            
            if (isCommonPrefix(strs, mid)) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }
        
        return strs[0].substr(0, left);
    }
    
    // Method 4: Trie-based approach (optimal for multiple queries)
    static std::string trieApproach(const std::vector<std::string>& strs) {
        if (strs.empty()) return "";
        if (strs.size() == 1) return strs[0];
        
        // Build trie
        TrieNode* root = new TrieNode();
        for (const auto& str : strs) {
            insertTrie(root, str);
        }
        
        // Find longest common prefix
        std::string result = "";
        TrieNode* current = root;
        
        while (current && current->children.size() == 1 && !current->isEndOfWord) {
            auto it = current->children.begin();
            result += it->first;
            current = it->second;
        }
        
        // Clean up memory
        deleteTrie(root);
        return result;
    }
    
    // Method 5: Most optimized version (combines best practices)
    static std::string optimized(const std::vector<std::string>& strs) {
        if (strs.empty()) return "";
        if (strs.size() == 1) return strs[0];
        
        // Early termination for empty strings
        for (const auto& str : strs) {
            if (str.empty()) return "";
        }
        
        // Find minimum length efficiently
        size_t minLen = strs[0].length();
        for (size_t i = 1; i < strs.size(); ++i) {
            if (strs[i].length() < minLen) {
                minLen = strs[i].length();
            }
        }
        
        // Vertical scanning with early termination
        for (size_t i = 0; i < minLen; ++i) {
            char currentChar = strs[0][i];
            for (size_t j = 1; j < strs.size(); ++j) {
                if (strs[j][i] != currentChar) {
                    return strs[0].substr(0, i);
                }
            }
        }
        
        return strs[0].substr(0, minLen);
    }

private:
    // Helper function for binary search
    static bool isCommonPrefix(const std::vector<std::string>& strs, int len) {
        std::string prefix = strs[0].substr(0, len);
        
        for (size_t i = 1; i < strs.size(); ++i) {
            if (strs[i].substr(0, len) != prefix) {
                return false;
            }
        }
        return true;
    }
    
    // Trie node structure
    struct TrieNode {
        std::unordered_map<char, TrieNode*> children;
        bool isEndOfWord;
        
        TrieNode() : isEndOfWord(false) {}
    };
    
    // Helper functions for trie
    static void insertTrie(TrieNode* root, const std::string& word) {
        TrieNode* current = root;
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
        }
        current->isEndOfWord = true;
    }
    
    static void deleteTrie(TrieNode* node) {
        if (!node) return;
        for (auto& pair : node->children) {
            deleteTrie(pair.second);
        }
        delete node;
    }
};

// Performance testing function
void performanceTest() {
    std::vector<std::string> testCases[] = {
        {"flower", "flow", "flight"},
        {"dog", "racecar", "car"},
        {"", "b"},
        {"a"},
        {"ab", "a"},
        {"abab", "aba", "abc"},
        {"a", "a", "a"},
        {"aa", "aa", "aa"},
        {"aaa", "aa", "aaa"},
        {"", "", ""},
        {"c", "c"},
        {"baab", "bacb", "b", "cbc"}
    };
    
    std::cout << "Testing all methods:\n";
    std::cout << "===================\n";
    
    for (size_t i = 0; i < sizeof(testCases) / sizeof(testCases[0]); ++i) {
        std::cout << "Test case " << (i + 1) << ": ";
        for (const auto& str : testCases[i]) {
            std::cout << "\"" << str << "\" ";
        }
        std::cout << "\n";
        
        std::cout << "Horizontal: \"" << LongestCommonPrefix::horizontalScanning(testCases[i]) << "\"\n";
        std::cout << "Vertical:   \"" << LongestCommonPrefix::verticalScanning(testCases[i]) << "\"\n";
        std::cout << "Binary:     \"" << LongestCommonPrefix::binarySearch(testCases[i]) << "\"\n";
        std::cout << "Optimized:  \"" << LongestCommonPrefix::optimized(testCases[i]) << "\"\n";
        std::cout << "---\n";
    }
}

int main() {
    // Example usage
    std::vector<std::string> strs = {"flower", "flow", "flight"};
    
    std::cout << "Input: ";
    for (const auto& str : strs) {
        std::cout << "\"" << str << "\" ";
    }
    std::cout << "\n\n";
    
    std::cout << "Longest Common Prefix: \"" 
              << LongestCommonPrefix::optimized(strs) << "\"\n\n";
    
    // Run performance tests
    performanceTest();
    
    return 0;
}