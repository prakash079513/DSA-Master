# 960. Delete Columns to Make Sorted III

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

You are given `n` strings of equal length `W`.

You want to **delete the minimum number of columns** so that **after deletion**, the rows are **lexicographically sorted**.

Equivalently:

- Choose some columns to **keep**
- The kept columns must preserve **non-decreasing order row-wise**
- Maximize kept columns ⇒ minimize deleted columns

---

## Key Insight (Core Idea)

Instead of thinking about deleting columns, think about:

> What is the maximum number of columns we can keep such that all rows stay sorted?

This becomes a **Longest Increasing Subsequence (LIS)** problem on columns.

---

## Observation

For two columns `i < j`, column `j` can come after column `i` **iff**:

For **every row**

`A[row][i] <= A[row][j]`

If this holds, column `j` can extend the sequence after `i`.

---

## Approach (DP / LIS on columns)

### State

`dp[i]` = maximum number of columns we can keep **starting from column i** (or ending at i, both views work)

### Transition

For all `j > i`:

- Check if column `j` is valid after `i` (for all rows)
- If valid:
  ```
  dp[i] = max(dp[i], 1 + dp[j])
  ```

### Base Case

Each column alone is valid:

```
dp[i] = 1
```

### Final Answer

```
maxKept = max(dp[i])
answer = W - maxKept
```

---

## Why this works

- Columns are ordered by index → natural LIS order
- Comparison is **row-wise**, not numeric
- Time is acceptable because `W ≤ 100`

This is **not greedy**, and **sorting columns independently is trash** here — DP is required.

---

## C++ Code

```cpp
int minDeletionSize(vector<string>& A) {
    int n = A.size();
    int W = A[0].size();

    vector<int> dp(W, 1);

    for (int i = W - 2; i >= 0; i--) {
        for (int j = i + 1; j < W; j++) {
            bool ok = true;
            for (int r = 0; r < n; r++) {
                if (A[r][i] > A[r][j]) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                dp[i] = max(dp[i], 1 + dp[j]);
            }
        }
    }

    int kept = 0;
    for (int x : dp) kept = max(kept, x);

    return W - kept;
}
```

## Complexity Analysis

### Complexity Analysis

**Time Complexity:** `O(W² × N)` – For each column pair, we compare all rows.

**Space Complexity:** `O(W)` – DP array over columns.

---

THE END
