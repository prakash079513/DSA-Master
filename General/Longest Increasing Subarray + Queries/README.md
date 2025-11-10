# Longest Increasing Subarray + Queries

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

You are given an array `arr` of size `n`, and a series of `q` queries represented as a string of characters where each character is either `L` or `R`.

- If the query is `L`: move the **last** element of the array to the **front**.
- If the query is `R`: move the **first** element of the array to the **end**.

After each operation, find the **length of the longest increasing contiguous subarray** in the modified array.

Return a vector of integers where each element corresponds to the LIS length after each query.

Example

Input:

`arr = [1, 2, 3]`

`queries = "LR"`

Operations:

- After `L`: `[3, 1, 2]` → LIS length = 2 (`[1, 2]`)
- After `R`: `[1, 2, 3]` → LIS length = 3

Output: `[2, 3]`

## Brute Force Approach (Straightforward)

Approach

- For each query:
  - Perform the rotation based on L or R.
  - Scan the array once to compute the **longest increasing contiguous subarray**.
  - Store the result.
- Return all LIS lengths.

Why it's fine

- This is okay for small constraints (e.g., `n ≤ 10^3`, `q ≤ 10^3`).
- Shows clear understanding of string operations and simple LIS length calculation.

### Code

```cpp
int findLIS(vector<int>& arr) {
    int n = arr.size();
    int best = 1, cur = 1;
    for (int i = 1; i < n; ++i) {
        if (arr[i] > arr[i - 1]) cur++;
        else cur = 1;
        best = max(best, cur);
    }
    return best;
}

vector<int> queryLIS(vector<int> arr, string q) {
    vector<int> res;
    for (char c : q) {
        if (c == 'L') {
            int last = arr.back();
            arr.pop_back();
            arr.insert(arr.begin(), last);
        } else if (c == 'R') {
            int first = arr.front();
            arr.erase(arr.begin());
            arr.push_back(first);
        }
        res.push_back(findLIS(arr));
    }
    return res;
}
```

## Expected / Interview Approach (Optimized for Real Tests)

Approach

- Notice that only **rotations** are applied; the relative order among elements stays the same.
- The LIS length of contiguous increasing sequence depends only on **breakpoints** where `arr[i] >= arr[i+1]`.
- When we rotate, these breakpoints shift circularly.
- Precompute all segment lengths in circular form.

Steps

1. Compute the **LIS length for all circular rotations** of the array in one pass:
   - Concatenate array with itself (size 2n).
   - For each window of size `n`, compute LIS length efficiently.
2. Maintain a pointer `start` that tracks the beginning of the rotated view.
   - When query `L`: `start = (start - 1 + n) % n`.
   - When query `R`: `start = (start + 1) % n`.
3. Return the precomputed LIS for each `start`.

Why this is good

- Demonstrates awareness of rotation equivalence.
- Converts repeated operations into **circular indexing** and precomputation.
- Avoids redoing `O(n)` scanning for each query.

### Efficient Code

```cpp
int lisLength(vector<int>& a, int start, int n) {
    int len = 1, best = 1;
    for (int i = 1; i < n; ++i) {
        int prev = a[(start + i - 1) % n];
        int cur = a[(start + i) % n];
        if (cur > prev) len++;
        else len = 1;
        best = max(best, len);
    }
    return best;
}

vector<int> queryLIS(vector<int>& arr, string q) {
    int n = arr.size();
    int start = 0;
    vector<int> res;
    for (char c : q) {
        if (c == 'L') start = (start - 1 + n) % n;
        else start = (start + 1) % n;
        res.push_back(lisLength(arr, start, n));
    }
    return res;
}
```

### Complexity Analysis

**Time Complexity:** `O(n * q)` – LIS length recalculated each rotation.

**Space Complexity:** `O(1)` – only uses fixed-size variables.

With slight precomputation tricks, it can even be optimized further to amortized `O(1)` per query for fixed patterns, but `O(n * q)` is acceptable and standard for interviews.

---

THE END
