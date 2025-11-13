# Maximum Elements Within Any Sliding Integer Window of Size _k_ in a Sorted Array

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

You are given a **sorted array** `arr[]` of size `n`, and a **window size** `k`.

For every possible integer window `[x, x + k - 1]` that can exist between `arr[0]` and `arr[n - 1] + k - 1`,

find the **maximum number of elements** from `arr` that fall inside any such window.

Formally,

Return the **maximum count of array elements** that can fit within any integer interval of length `k`.

---

### Example

Input:

`arr = [2, 3, 7, 8], k = 3`

Possible integer windows and counts:

- [2, 4] → elements = {2, 3} → count = 2
- [3, 5] → {3} → count = 1
- [4, 6] → {} → count = 0
- [5, 7] → {7} → count = 1
- [6, 8] → {7, 8} → count = 2

**Maximum = 2**

Output:

`2`

---

### Approach (Optimal `O(n)` using Two Pointers)

- Since the array is **sorted**, we can use a **sliding window (two pointers)** approach.
- Maintain two indices `l` and `r` representing the current window in the array.
- For each `r`, move `l` forward while `arr[r] - arr[l] >= k` (since the window length exceeds `k-1`).
- The number of elements in the current window is `r - l + 1`.
- Keep updating the maximum count.

---

### Code

```cpp
int maxInWindow(vector<int>& arr, int k) {
    int n = arr.size();
    int l = 0, maxCount = 0;
    for (int r = 0; r < n; r++) {
        while (arr[r] - arr[l] >= k)
            l++;
        maxCount = max(maxCount, r - l + 1);
    }
    return maxCount;
}
```

---

### Complexity Analysis

**Time Complexity:** `O(n)` – Each element is visited at most twice (once by `l`, once by `r`).

**Space Complexity:** `O(1)` – Only constant extra space is used.

---

THE END
