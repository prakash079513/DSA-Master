# Longest Common Substring

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

Given two strings `s1` and `s2`, find the length of the longest substring that is present in both strings.

- A substring is a sequence of characters that appear **contiguously** in the same order.
- If no common substring exists, return 0.

## Editorial

### Approach (Dynamic Programming)

The **Longest Common Substring** problem is different from **Longest Common Subsequence**.

- Substring must be _continuous_, while subsequence can skip characters.
- So, if characters don’t match, the current streak breaks and we reset.

We use a **2D DP table** `dp[m+1][n+1]`, where

- `dp[i][j]` = length of the longest common substring **ending at** `s1[i-1]` and `s2[j-1]`.

### Steps:

1. Initialize a matrix `dp` with size `(m+1) x (n+1)` filled with zeros.
2. Traverse through both strings:
   - If `s1[i-1] == s2[j-1]`, then `dp[i][j] = 1 + dp[i-1][j-1]`.
   - Else, `dp[i][j] = 0` (because substring continuity breaks).
3. Keep track of a global maximum length while filling the table.

This guarantees the longest contiguous match.

### Code

```cpp
int lcstr(string s1, string s2) {
    int m = s1.size(), n = s2.size();
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    int result = 0;

    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(s1[i-1] == s2[j-1]) {
                dp[i][j] = 1 + dp[i-1][j-1];
                result = max(result, dp[i][j]);
            }
            else {
                dp[i][j] = 0;
            }
        }
    }
    return result;
}
```

### Complexity Analysis

**Time Complexity:** `O(m*n)` – every cell in the DP table is filled once.

**Space Complexity:** `O(m*n)` – storing the DP table.

---

## Space Optimization

Notice in the recurrence:

`dp[i][j] = 1 + dp[i-1][j-1]`

We only need the **previous row (i-1)** to compute the current row. So instead of storing the whole table, we keep only **two arrays**:

- `prev[n+1]` → stores dp values for row `i-1`.
- `curr[n+1]` → stores dp values for row `i`.

After processing each row, set `prev = curr` and reset `curr`.

---

### Code

```cpp
int longestCommonSubstr(string s1, string s2) {
    int m = s1.size(), n = s2.size();
    vector<int> prev(n+1, 0), curr(n+1, 0);
    int result = 0;

    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(s1[i-1] == s2[j-1]) {
                curr[j] = 1 + prev[j-1];
                result = max(result, curr[j]);
            }
            else {
                curr[j] = 0;
            }
        }
        prev = curr;
    }
    return result;
}
```

### Complexity Analysis

**Time Complexity:** `O(m*n)` – same as before, since every pair `(i,j)` is checked.

**Space Complexity:** `O(n)` – only two rows of length `n` are maintained.

---
