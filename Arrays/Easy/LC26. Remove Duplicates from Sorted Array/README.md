# **26. Remove Duplicates from Sorted Array**

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

You are given a **sorted** integer array `nums`. Remove the duplicates **in-place** such that each unique element appears only once. Return the number of unique elements. The relative order **must be preserved**.

## Brute Force Approach

- Traverse the array and insert elements into a set or another array
- Copy unique elements back into `nums`
- Return the size of the set

**Time Complexity: `O(n)`**

**Space Complexity: `O(n)`**

## Two Pointers – In-place

### Key Observation

- The array is **already sorted**
- Duplicates are **adjacent**
- We only need to keep one occurrence of each number

### Approach

- Use pointer `k` to track position of next unique element
- Start `k = 1` (first element is always unique)
- Traverse from index `1` to `n-1`
- If `nums[i] != nums[k-1]`
  - Assign `nums[k] = nums[i]`
  - Increment `k`
- First `k` elements of `nums` are the answer

## Code

```cpp
int removeDuplicates(vector<int>& nums) {
    if (nums.size() == 0) return 0;

    int k = 1;

    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] != nums[k - 1]) {
            nums[k] = nums[i];
            k++;
        }
    }
    return k;
}
```

**Time Complexity:** `O(n)` – single pass through the array

**Space Complexity:** `O(1)` – in-place, no extra memory

---

THE END
