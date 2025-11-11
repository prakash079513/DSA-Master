# Maximum Subarray Kadane’s Algorithm

**LeetCode #53**

**Author:** [Prakash JC](https://prakash079513.github.io/)

## Problem Statement

You are given an integer array `nums`.

Find the **contiguous subarray** (containing at least one number) which has the **largest sum**, and return _its sum_.

Example:

```
Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.
```

## Brute Force Approach

### Idea

- Check all possible subarrays and calculate their sums.
- Keep track of the maximum sum seen so far.

### Steps

1. Iterate over every starting index `i`.
2. For each `i`, iterate over every ending index `j >= i`.
3. Compute the sum of elements from `i` to `j`.
4. Update the maximum whenever a larger sum is found.

This approach directly explores all subarrays, which is simple but inefficient.

---

### Code

```cpp
int maxSubArray(vector<int>& nums) {
    int n = nums.size();
    int maxSum = INT_MIN;
    for (int i = 0; i < n; i++) {
        int currentSum = 0;
        for (int j = i; j < n; j++) {
            currentSum += nums[j];
            maxSum = max(maxSum, currentSum);
        }
    }
    return maxSum;
}
```

---

### Complexity Analysis

**Time Complexity:** `O(n²)` – Two nested loops for all subarrays.

**Space Complexity:** `O(1)` – Only a few variables used.

---

## Optimal Approach (Kadane’s Algorithm)

### Idea

Instead of recalculating subarray sums, **use dynamic accumulation**:

- Keep a running sum `currSum`.
- Add the current element to `currSum`.
- If `currSum` becomes negative, reset it to `0` (since a negative prefix cannot help future subarrays).
- Keep track of the maximum sum found so far.

This way, you efficiently compute the best subarray ending at each index in a single pass.

### Dry run

Array: `[-2, 1, -3, 4, -1, 2, 1, -5, 4]`

We want to find the contiguous subarray with the **maximum sum**.

**Initialization**

| Variable  | Meaning                              | Initial Value           |
| --------- | ------------------------------------ | ----------------------- |
| `currSum` | Running sum till the current element | `0`                     |
| `maxSum`  | Maximum sum found so far             | `-∞` (or first element) |

**Step-by-step Dry Run**

| Index | Element | `currSum` Before | `currSum` After                                 | `maxSum`           | Comment                        |
| ----- | ------- | ---------------- | ----------------------------------------------- | ------------------ | ------------------------------ |
| 0     | -2      | 0                | `0 + (-2) = -2` → reset to `0` (since negative) | `max(-∞, -2) = -2` | Negative, reset                |
| 1     | 1       | 0                | `0 + 1 = 1`                                     | `max(-2, 1) = 1`   | Start new subarray             |
| 2     | -3      | 1                | `1 + (-3) = -2` → reset to `0`                  | `max(1, -2) = 1`   | Negative, reset                |
| 3     | 4       | 0                | `0 + 4 = 4`                                     | `max(1, 4) = 4`    | Start new subarray             |
| 4     | -1      | 4                | `4 + (-1) = 3`                                  | `max(4, 3) = 4`    | Keep subarray                  |
| 5     | 2       | 3                | `3 + 2 = 5`                                     | `max(4, 5) = 5`    | Better sum found               |
| 6     | 1       | 5                | `5 + 1 = 6`                                     | `max(5, 6) = 6`    | Keep extending                 |
| 7     | -5      | 6                | `6 + (-5) = 1`                                  | `max(6, 1) = 6`    | Drop in sum but still positive |
| 8     | 4       | 1                | `1 + 4 = 5`                                     | `max(6, 5) = 6`    | Final step                     |

### Final Result

**Maximum Subarray Sum = 6**

**Subarray contributing to this = [4, -1, 2, 1]**

---

**Summary of Logic**

- If `currSum` < 0 → discard it (`currSum = 0`).
- Else → keep adding.
- Track global max every step.

---

### Implementation

1. Initialize `maxSum = nums[0]` and `currSum = 0`.
2. For each element `x` in `nums`:
   - Add it to `currSum`.
   - Update `maxSum = max(maxSum, currSum)`.
   - If `currSum < 0`, reset `currSum = 0`.
3. Return `maxSum`.

---

### Code

```cpp
int maxSubArray(vector<int>& nums) {
    int maxSum = nums[0];
    int currSum = 0;

    for (int x : nums) {
        currSum += x;
        maxSum = max(maxSum, currSum);
        if (currSum < 0) currSum = 0;
    }
    return maxSum;
}
```

---

### Complexity Analysis

**Time Complexity:** `O(n)` – Single pass through the array.

**Space Complexity:** `O(1)` – Constant extra space.

---

### Intuition Recap

Kadane’s Algorithm dynamically extends or resets the subarray:

- If adding the current element increases the sum → extend it.
- If it reduces the sum (goes negative) → start a new subarray.

This ensures that at every step, the best possible subarray ending at that position is considered.

---

**THE END**
