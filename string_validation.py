def can_form_string(s, counts):
    """
    Determine if string s can be formed using available words.
    
    Args:
        s: The target string to form
        counts: Array [count_A, count_B, count_AB, count_BA] representing
                available uses of words A, B, AB, BA respectively
    
    Returns:
        1 if s can be formed, 0 otherwise
    """
    if not s:
        return 1
    
    # Available words and their counts
    words = ["A", "B", "AB", "BA"]
    word_counts = counts[:]  # Make a copy to avoid modifying original
    
    # Use dynamic programming with memoization
    memo = {}
    
    def can_form(remaining_string, remaining_counts):
        # Convert to tuple for hashing
        key = (remaining_string, tuple(remaining_counts))
        if key in memo:
            return memo[key]
        
        # Base case: empty string can always be formed
        if not remaining_string:
            memo[key] = True
            return True
        
        # Try each available word
        for i, word in enumerate(words):
            # Check if we have this word available and if it matches the start of remaining string
            if remaining_counts[i] > 0 and remaining_string.startswith(word):
                # Use this word
                new_counts = remaining_counts[:]
                new_counts[i] -= 1
                new_remaining = remaining_string[len(word):]
                
                # Recursively check if the rest can be formed
                if can_form(new_remaining, new_counts):
                    memo[key] = True
                    return True
        
        # No valid word found
        memo[key] = False
        return False
    
    result = can_form(s, word_counts)
    return 1 if result else 0


def solve_examples():
    """Test the function with the provided examples"""
    
    # Example 1: s = "B", counts = [1,0,0,0]
    s1 = "B"
    counts1 = [1, 0, 0, 0]
    result1 = can_form_string(s1, counts1)
    print(f"Example 1: s = '{s1}', counts = {counts1}")
    print(f"Result: {result1} (Expected: 0)")
    print(f"Explanation: We have 1 'A' but need 'B', so impossible\n")
    
    # Example 2: s = "ABAB", counts = [1,1,0,1] 
    s2 = "ABAB"
    counts2 = [1, 1, 0, 1]
    result2 = can_form_string(s2, counts2)
    print(f"Example 2: s = '{s2}', counts = {counts2}")
    print(f"Result: {result2} (Expected: 1)")
    print(f"Explanation: Can form as A + B + AB or AB + AB (but we only have 0 AB), so A + B + AB works\n")
    
    # Additional test cases
    print("Additional test cases:")
    
    # Test case 3: Empty string
    result3 = can_form_string("", [0, 0, 0, 0])
    print(f"Empty string: {result3} (Expected: 1)")
    
    # Test case 4: Simple A
    result4 = can_form_string("A", [1, 0, 0, 0])
    print(f"'A' with [1,0,0,0]: {result4} (Expected: 1)")
    
    # Test case 5: AB using AB word
    result5 = can_form_string("AB", [0, 0, 1, 0])
    print(f"'AB' with [0,0,1,0]: {result5} (Expected: 1)")
    
    # Test case 6: AB using A and B words
    result6 = can_form_string("AB", [1, 1, 0, 0])
    print(f"'AB' with [1,1,0,0]: {result6} (Expected: 1)")


if __name__ == "__main__":
    solve_examples()