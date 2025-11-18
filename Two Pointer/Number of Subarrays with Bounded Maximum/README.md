# Number of Subarrays with Bounded Maximum

**LeetCode #795**

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

You are given an integer array `nums` and two integers `left` and `right`.

Return the number of non-empty subarrays such that the maximum element of the subarray lies in the range:

```
left ≤ max(subarray) ≤ right
```

---

# Brute Force Approach

### Approach

- Iterate over every possible start index `i`.
- Extend the subarray to every end index `j >= i`.
- Track the maximum element of the current subarray.
- If the maximum lies within `[left, right]`, increment the result.
- Simple but slow.

---

### Code

```cpp
int numSubarrayBoundedMax(vector<int>& nums, int left, int right) {
    int n = nums.size();
    int count = 0;

    for (int i = 0; i < n; i++) {
        int mx = INT_MIN;
        for (int j = i; j < n; j++) {
            mx = max(mx, nums[j]);
            if (mx >= left && mx <= right)
                count++;
        }
    }
    return count;
}
```

### Complexity Analysis

Time Complexity: `O(n^2)` – all subarrays considered.

Space Complexity: `O(1)` – constant extra space.

## Expected Optimal Two-Pointer / Index Tracking Approach

This is the standard accepted solution.

### Idea

Classify elements:

- If `nums[i] > right`: bad element, breaks all subarrays containing it.
- If `nums[i] < left`: neutral, does not make a subarray valid by itself.
- If `left ≤ nums[i] ≤ right`: valid element, guarantees subarrays ending here are valid.

Maintain two important indices:

- `lastBad`: last index where `nums[i] > right`.
- `lastValid`: last index where `left ≤ nums[i] ≤ right`.

For each index `i`, the number of valid subarrays ending at `i` is:

```
max(0, lastValid - lastBad)
```

Because:

- Start of the subarray must be strictly after the last bad element.
- Start can go up to lastValid because that guarantees the subarray has a maximum in range.

---

### Detailed Dry Run (Length 7 Example)

Let:

```
nums = [2, 1, 5, 1, 3, 2, 4]
left = 2
right = 3
```

Meaning: only subarrays whose maximum is 2 or 3 are allowed.

Classify:

- valid_big = element in [2,3]
- small = element < 2
- bad = element > 3

Tracking table:

| i   | nums[i] | type      | lastBad | lastValid | lastValid - lastBad | count added | Explanation                      |
| --- | ------- | --------- | ------- | --------- | ------------------- | ----------- | -------------------------------- |
| 0   | 2       | valid_big | -1      | 0         | 1                   | +1          | [2]                              |
| 1   | 1       | small     | -1      | 0         | 1                   | +1          | [2,1]                            |
| 2   | 5       | bad       | 2       | 0         | -2                  | +0          | reset zone                       |
| 3   | 1       | small     | 2       | 0         | -2                  | +0          | still no valid_big after lastBad |
| 4   | 3       | valid_big | 2       | 4         | 2                   | +2          | [3], [1,3]                       |
| 5   | 2       | valid_big | 2       | 5         | 3                   | +3          | [2], [3,2], [1,3,2]              |
| 6   | 4       | bad       | 6       | 5         | -1                  | +0          | reset                            |

Total = 1 + 1 + 0 + 0 + 2 + 3 + 0 = 7 valid subarrays.

---

### Code (Optimal)

```cpp
int numSubarrayBoundedMax(vector<int>& nums, int left, int right) {
    int n = nums.size();
    int lastBad = -1, lastValid = -1;
    int ans = 0;

    for (int i = 0; i < n; i++) {
        if (nums[i] > right)
            lastBad = i;

        if (nums[i] >= left && nums[i] <= right)
            lastValid = i;

        ans += max(0, lastValid - lastBad);
    }
    return ans;
}
```

---

### Complexity Analysis

Time Complexity: `O(n)`

Single pass through array while maintaining two indices.

Space Complexity: `O(1)`

Only constant extra variables.

---

THE END
