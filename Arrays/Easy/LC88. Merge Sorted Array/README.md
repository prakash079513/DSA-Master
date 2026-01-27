# 88. Merge Sorted Array

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

You are given two sorted integer arrays `nums1` and `nums2`, with sizes `m` and `n` respectively.

`nums1` has enough extra space at the end (size `m + n`) to hold all elements of `nums2`.

Merge `nums2` into `nums1` so that `nums1` becomes a single sorted array.

## Approach (Optimal – In-place, Two Pointers from Back)

- The valid elements of `nums1` are only in indices `0` to `m-1`
- The extra space is at the **end**, so merging from the **back** avoids overwriting useful data
- Use three pointers:
  - `i` → last valid element of `nums1` (`m-1`)
  - `j` → last element of `nums2` (`n-1`)
  - `k` → last index of `nums1` (`m+n-1`)
- Compare `nums1[i]` and `nums2[j]`
- Place the larger element at `nums1[k]` and move pointers
- After one array finishes, copy remaining elements of `nums2` (if any)
- No need to copy remaining `nums1` elements — they are already in place

This avoids sorting, avoids extra space, and is exactly what the problem expects.

## Code (C++)

```cpp
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = m - 1;
    int j = n - 1;
    int k = m + n - 1;

    while (i >= 0 && j >= 0) {
        if (nums1[i] > nums2[j])
            nums1[k--] = nums1[i--];
        else
            nums1[k--] = nums2[j--];
    }

    while (j >= 0) {
        nums1[k--] = nums2[j--];
    }
}
```

## Complexity Analysis

**Time Complexity:** `O(m + n)` – each element is processed once

**Space Complexity:** `O(1)` – in-place merge, no extra memory used

## Why brute force is bad here

- Copy + sort leads to `O((m+n) log(m+n))`
- Detecting `0` as empty space is incorrect (0 can be valid data)
- Interviewers expect pointer logic, not sorting

This solution is **optimal, interview-approved, and clean**.

---

THE END
