# Power Array Optimization Algorithm

## Problem Statement

Given an integer array A of length N, we need to find the largest possible power array for any permutation P.

The power array X is defined as:
- X[i] = maximum j such that ∀ k ≤ j (Z[k] & 2^(20-i) ≠ 0) where 1 ≤ i ≤ 20
- Z = [A[P[1]], A[P[2]], ..., A[P[N]]] is the permuted array

A power array F is greater than G if there exists an index i such that F[i] > G[i] and ∀ j < i, F[j] = G[j] (lexicographic comparison).

## Algorithm Explanation

### Key Insight

To maximize the power array lexicographically, we need to maximize X[1] first, then X[2], and so on.

For X[i], we want to find the maximum prefix length where all elements have bit (20-i) set. This is equivalent to counting how many elements in the array have bit (20-i) set, because we can always arrange those elements at the beginning of our permutation.

### Algorithm Steps

1. **For each bit position i from 1 to 20:**
   - Calculate the bit value: `bit_value = 2^(20-i)`
   - Count how many elements in array A have this bit set
   - Set `X[i] = count`

2. **Why this works:**
   - Since we can choose any permutation, we can always place all elements with a specific bit set at the beginning
   - The maximum prefix length where all elements have bit (20-i) set is exactly the count of such elements
   - This greedy approach gives us the lexicographically largest power array

### Time Complexity
- O(20 × N) = O(N) where N is the length of array A

### Space Complexity
- O(20) = O(1) for the power array

## Example Walkthrough

**Input:** A = [1, 2, 3, 4]

Binary representations:
- 1 = 00000000000000000001
- 2 = 00000000000000000010  
- 3 = 00000000000000000011
- 4 = 00000000000000000100

**For each bit position:**

- X[1] (bit 19): Count elements with bit 2^19 set = 0
- X[2] (bit 18): Count elements with bit 2^18 set = 0
- ...
- X[17] (bit 3): Count elements with bit 2^3 set = 0
- X[18] (bit 2): Count elements with bit 2^2 set = 1 (only 4)
- X[19] (bit 1): Count elements with bit 2^1 set = 2 (2 and 3)
- X[20] (bit 0): Count elements with bit 2^0 set = 2 (1 and 3)

**Result:** [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2]

## Optimal Permutation Construction

While the problem only asks for the power array, the optimal permutation can be constructed as follows:

1. Start with an empty permutation
2. For each bit position from most significant to least significant:
   - Add all elements with that bit set to the permutation
   - Remove these elements from consideration
3. Add any remaining elements at the end

This ensures that for each bit position, we maximize the prefix length of elements with that bit set.