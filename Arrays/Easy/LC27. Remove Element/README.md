# 27. Remove Element

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

Given an integer array `nums` and an integer `val`, remove all occurrences of `val` **in-place** and return the number of elements remaining.

The relative order of elements **does not matter**.

## Approach 1: Brute Force (Shifting Elements)

- Traverse the array from left to right
- Whenever `nums[i] == val`
  - Shift all elements to the left by one position
  - Reduce array size
  - Stay at the same index to recheck the new value
- Continue until the end

### Why this is bad

- Each deletion causes a shift
- Too slow for large inputs

### Time Complexity: `O(n^2)`

### Space Complexity: `O(1)`

## Approach 2: Optimal (Two Pointers – Overwrite Method)

- Use one pointer `k` to track the index for valid elements
- Traverse array with index `i`
- If `nums[i] != val`
  - Assign `nums[k] = nums[i]`
  - Increment `k`
- At the end:
  - First `k` elements are valid
  - Elements after `k` don’t matter

This works because:

- Order preservation is allowed
- Overwriting avoids shifting

## Code (C++)

```cpp
int removeElement(vector<int>& nums, int val) {
    int k = 0;

    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != val) {
            nums[k] = nums[i];
            k++;
        }
    }
    return k;
}
```

## Complexity Analysis

**Time Complexity:** `O(n)` – single pass through the array

**Space Complexity:** `O(1)` – in-place, no extra memory

## Interview Notes (Important)

- Do **not** use extra arrays
- Do **not** sort
- Do **not** assume anything about values (like `0` being empty)
- Two-pointer overwrite is the **expected** solution

---

THE END
