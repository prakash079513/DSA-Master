## **1929. Concatenation of Array**

Author: Prakash JC

## Problem Statement

Given an integer array `nums` of length `n`, you want to create an array `ans` of length `2n` where:

- `ans[i] = nums[i]` for `0 <= i < n`
- `ans[i + n] = nums[i]` for `0 <= i < n`

Return the array `ans`.

---

### Key Takeaway

- Just push back each element to the original array.

---

## Brute Force Approach

### Approach

- Create a new array `ans` of size `2n`
- Copy all elements of `nums` into `ans`
- Copy all elements of `nums` again into `ans`
- Return `ans`

**Time Complexity: `O(n)`**

**Space Complexity: `O(n)`**

---

## Optimal Approach – In-place Expansion

### Key Observation

- We need to append the same elements again
- Vector allows dynamic resizing using `push_back`
- Directly modifying the original array is allowed

### Approach

- Store original size `n`
- Traverse from `0` to `n-1`
- For each element, push it back into `nums`
- Return modified `nums`

---

## Code

```cpp
vector<int> concatenatee(vector<int>& nums) {
    int n = nums.size();

    for (int i = 0; i < n; i++) {
        nums.push_back(nums[i]);
    }

    return nums;
}
```

---

**Time Complexity:** `O(n)` – single traversal

**Space Complexity:** `O(1)` – no extra array (output excluded)

---

THE END
