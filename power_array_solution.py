def solve(A):
    """
    Given an integer array A of length N, find the largest possible power array
    for any permutation.
    
    Power array X[i] = maximum j such that for all k <= j, Z[k] & 2^(20-i) != 0
    where Z is the permuted array and 1 <= i <= 20
    """
    N = len(A)
    
    # For each bit position (from most significant to least significant)
    # we want to maximize the prefix length where all elements have that bit set
    
    power_array = [0] * 20
    
    # We'll use a greedy approach: for each bit position, we want to place
    # elements with that bit set as early as possible in the permutation
    
    # Create the optimal permutation
    remaining = A[:]
    permutation = []
    
    for bit_pos in range(20):  # bit positions 0 to 19 (corresponding to 2^19 to 2^0)
        bit_value = 1 << (19 - bit_pos)  # 2^(19-bit_pos)
        
        # Find all remaining elements that have this bit set
        elements_with_bit = []
        elements_without_bit = []
        
        for num in remaining:
            if num & bit_value:
                elements_with_bit.append(num)
            else:
                elements_without_bit.append(num)
        
        # Add elements with the bit set first
        permutation.extend(elements_with_bit)
        
        # Calculate power_array[bit_pos]
        # This is the maximum j such that all Z[k] for k <= j have bit_value set
        power_array[bit_pos] = len(elements_with_bit)
        
        # Update remaining elements for next iteration
        remaining = elements_without_bit
    
    # Add any remaining elements (those that don't have any of the processed bits)
    permutation.extend(remaining)
    
    return power_array

def solve_optimized(A):
    """
    Optimized version that directly computes the power array without
    explicitly constructing the permutation.
    """
    N = len(A)
    power_array = [0] * 20
    
    # For each bit position from most significant to least significant
    for i in range(20):
        bit_value = 1 << (19 - i)  # 2^(20-i-1)
        
        # Count elements that have this bit set
        count = sum(1 for num in A if num & bit_value)
        power_array[i] = count
    
    return power_array

def test_solution():
    """Test the solution with sample cases"""
    
    # Test case 1: Simple case
    A1 = [1, 2, 3, 4]
    result1 = solve_optimized(A1)
    print(f"Test 1: A = {A1}")
    print(f"Power array: {result1}")
    print()
    
    # Test case 2: All same elements
    A2 = [7, 7, 7, 7]  # 7 = 111 in binary
    result2 = solve_optimized(A2)
    print(f"Test 2: A = {A2}")
    print(f"Power array: {result2}")
    print()
    
    # Test case 3: Powers of 2
    A3 = [1, 2, 4, 8, 16]  # Each is a single bit
    result3 = solve_optimized(A3)
    print(f"Test 3: A = {A3}")
    print(f"Power array: {result3}")
    print()
    
    # Test case 4: Large numbers
    A4 = [1048575, 524287, 262143]  # Numbers with many bits set
    result4 = solve_optimized(A4)
    print(f"Test 4: A = {A4}")
    print(f"Power array: {result4}")
    print()

if __name__ == "__main__":
    test_solution()