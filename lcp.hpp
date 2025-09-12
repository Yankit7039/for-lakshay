#ifndef LONGEST_COMMON_PREFIX_HPP
#define LONGEST_COMMON_PREFIX_HPP

#include <vector>
#include <string>
#include <algorithm>

/**
 * @brief Find the longest common prefix among a vector of strings
 * 
 * This is the most optimized implementation using vertical scanning.
 * 
 * Time Complexity: O(S) where S is the sum of all characters in all strings
 * Space Complexity: O(1) excluding the input vector
 * 
 * @param strs Vector of strings to find common prefix for
 * @return std::string The longest common prefix, empty string if no common prefix
 */
inline std::string longestCommonPrefix(const std::vector<std::string>& strs) {
    // Handle edge cases
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
    
    // Vertical scanning: compare character by character
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

/**
 * @brief Alternative optimized implementation using horizontal scanning
 * 
 * This version is more efficient when the common prefix is expected to be short
 * compared to the average string length.
 * 
 * @param strs Vector of strings to find common prefix for
 * @return std::string The longest common prefix
 */
inline std::string longestCommonPrefixHorizontal(const std::vector<std::string>& strs) {
    if (strs.empty()) return "";
    if (strs.size() == 1) return strs[0];
    
    std::string prefix = strs[0];
    
    for (size_t i = 1; i < strs.size() && !prefix.empty(); ++i) {
        size_t minLen = std::min(prefix.length(), strs[i].length());
        
        size_t j = 0;
        while (j < minLen && prefix[j] == strs[i][j]) {
            ++j;
        }
        
        prefix = prefix.substr(0, j);
    }
    
    return prefix;
}

#endif // LONGEST_COMMON_PREFIX_HPP