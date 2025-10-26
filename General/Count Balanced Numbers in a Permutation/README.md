# Count Balanced Numbers in a Permutation

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

You are given a permutation `p` of size `n` (all integers `1..n` appear exactly once).

A number `k` is called **balanced** if there exists a contiguous subarray of `p` that is a permutation of `{1..k}`.

Return a binary string `result` of length `n`, where:

- result[k-1] = `'1'` if `k` is balanced
- result[k-1] = `'0'` otherwise

---

## Intuition

For `{1..k}` to form a valid subarray:

- That subarray must have **length = k**
- It must contain the **maximum element = k**

Since elements are unique, if the positions of `{1..k}` fall inside a contiguous interval of length `k`, no other element can be inside that interval → valid balanced subarray.

So instead of checking values inside windows, track the **position range** where `{1..k}` appears:

- Let `min_index` = smallest position of numbers `1..k`
- Let `max_index` = largest position of numbers `1..k`

Then `k` is balanced **iff**

```
max_index - min_index + 1 == k
```

Great part? Adding `k` increases the set monotonically → we only update min/max once per step.

---

## Approach

- Build a `pos[]` array mapping each value to its index in `p`
- Initialize:
  - `min_index = n`
  - `max_index = -1`
- Loop `k = 1..n`:
  - Update extremes with position of `k`
  - If interval length equals `k`, mark result as `'1'`

---

## Code

```cpp
string countBalancedNumbers(vector<int> p) {
    int n = p.size();
    vector<int> pos(n + 1);

    for (int i = 0; i < n; ++i)
        pos[p[i]] = i;

    string result(n, '0');
    int min_index = n, max_index = -1;

    for (int k = 1; k <= n; ++k) {
        int current_pos = pos[k];

        min_index = min(min_index, current_pos);
        max_index = max(max_index, current_pos);

        if (max_index - min_index + 1 == k)
            result[k - 1] = '1';
    }
    return result;
}
```

---

### Complexity Analysis

**Time Complexity:** `O(n)` — one scan to build pos[], one scan for all k

**Space Complexity:** `O(n)` — position array and output string

---

THE END
