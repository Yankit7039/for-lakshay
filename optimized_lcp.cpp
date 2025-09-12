#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

/**
 * Most Optimized Longest Common Prefix Solution
 * 
 * Time Complexity: O(S) where S is the sum of all characters in all strings
 * Space Complexity: O(1) excluding the input vector
 * 
 * This solution uses vertical scanning with several optimizations:
 * 1. Early termination for empty strings
 * 2. Efficient minimum length calculation
 * 3. Character-by-character comparison with early exit
 * 4. No unnecessary string operations
 */
std::string longestCommonPrefix(const std::vector<std::string>& strs) {
    // Handle edge cases
    if (strs.empty()) return "";
    if (strs.size() == 1) return strs[0];
    
    // Early termination for empty strings
    for (const auto& str : strs) {
        if (str.empty()) return "";
    }
    
    // Find minimum length efficiently (single pass)
    size_t minLen = strs[0].length();
    for (size_t i = 1; i < strs.size(); ++i) {
        if (strs[i].length() < minLen) {
            minLen = strs[i].length();
        }
    }
    
    // Vertical scanning: compare character by character across all strings
    for (size_t i = 0; i < minLen; ++i) {
        char currentChar = strs[0][i];
        
        // Check if all strings have the same character at position i
        for (size_t j = 1; j < strs.size(); ++j) {
            if (strs[j][i] != currentChar) {
                // Return the common prefix up to position i
                return strs[0].substr(0, i);
            }
        }
    }
    
    // All characters up to minLen are common
    return strs[0].substr(0, minLen);
}

// Alternative: Even more optimized version for very large inputs
std::string longestCommonPrefixOptimized(const std::vector<std::string>& strs) {
    if (strs.empty()) return "";
    if (strs.size() == 1) return strs[0];
    
    // Use the first string as reference
    const std::string& first = strs[0];
    size_t prefixLen = first.length();
    
    // Compare with each subsequent string
    for (size_t i = 1; i < strs.size() && prefixLen > 0; ++i) {
        const std::string& current = strs[i];
        
        // Find the minimum length between current prefix and current string
        size_t minLen = std::min(prefixLen, current.length());
        
        // Find the actual common prefix length
        size_t j = 0;
        while (j < minLen && first[j] == current[j]) {
            ++j;
        }
        
        prefixLen = j;
    }
    
    return first.substr(0, prefixLen);
}

// Test function
void test() {
    std::vector<std::vector<std::string>> testCases = {
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
        {"baab", "bacb", "b", "cbc"},
        {"leetcode", "leet", "lee", "le"},
        {"interspecies", "interstellar", "interstate"},
        {"throne", "throne"},
        {"throne", "dungeon"}
    };
    
    std::cout << "Testing Longest Common Prefix Solutions:\n";
    std::cout << "========================================\n\n";
    
    for (size_t i = 0; i < testCases.size(); ++i) {
        std::cout << "Test " << (i + 1) << ": ";
        for (const auto& str : testCases[i]) {
            std::cout << "\"" << str << "\" ";
        }
        std::cout << "\n";
        
        std::string result1 = longestCommonPrefix(testCases[i]);
        std::string result2 = longestCommonPrefixOptimized(testCases[i]);
        
        std::cout << "Result 1: \"" << result1 << "\"\n";
        std::cout << "Result 2: \"" << result2 << "\"\n";
        std::cout << "---\n\n";
    }
}

int main() {
    // Example usage
    std::vector<std::string> strs = {"flower", "flow", "flight"};
    
    std::cout << "Input: ";
    for (const auto& str : strs) {
        std::cout << "\"" << str << "\" ";
    }
    std::cout << "\n";
    
    std::cout << "Longest Common Prefix: \"" 
              << longestCommonPrefix(strs) << "\"\n\n";
    
    // Run comprehensive tests
    test();
    
    return 0;
}