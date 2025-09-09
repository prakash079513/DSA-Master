# Distinct Subsequences

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

You are given two strings `s` and `t`. Find the number of distinct subsequences of `s` which equal `t`.

Example: `s = babgag` and `t = bag`.

## Editorial

## Recursion

Indices: `i` and `j`. Direction: `n-1` to `0`.

At each index `i` in `s` and `j` in `t`, we consider two cases:

1. **If** `s[i] == t[j]`:
   - We can take this match → recurse on `(i - 1, j - 1)`.
   - Or skip it → recurse on `(i - 1, j)`.
2. **If** `s[i] != t[j]`:
   - Only option is to skip **but** with the same `j` → recurse on `(i - 1, j)`.

Base cases:

Note: Problem is related to count ways. Hence it should be return `1` or `0`.

- If `j < 0`, that means `t` is completely matched → return `1`.
- If `i < 0` and `j >= 0`, that means `s` is exhausted but `t` is not → return `0`.

### Code

```cpp
int f(int i, int j, string &s, string &t) {
    if (j < 0) return 1;
    if (i < 0) return 0;

    if (s[i] == t[j]) {
        return f(i - 1, j - 1, s, t) + f(i - 1, j, s, t);
    }
    return f(i - 1, j, s, t);
}
```

### Complexity Analysis

**Time Complexity:** `O(2^n)` – At each step, we may branch into two recursive calls.

**Space Complexity:** `O(n + m)` – Recursion stack depth in the worst case.

---

## Memoization

- Use a `dp[i][j]` table where `dp[i][j]` stores the number of subsequences in `s[0..i]` that form `t[0..j]`.
- Before computing, check if the value is already stored.

### Code

```cpp
int f(int i, int j, string &s, string &t, vector<vector<int>>& dp) {
    if (j < 0) return 1;
    if (i < 0) return 0;

    if (dp[i][j] != -1) return dp[i][j];

    if (s[i] == t[j]) {
        return dp[i][j] = f(i - 1, j - 1, s, t, dp) + f(i - 1, j, s, t, dp);
    }
    return dp[i][j] = f(i - 1, j, s, t, dp);
}
```

### Complexity Analysis

**Time Complexity:** `O(n * m)` – Every state `(i, j)` is computed once.

**Space Complexity:** `O(n * m)` for the dp table + `O(n + m)` recursion stack.

---

## Tabulation

- `dp[i][j]` = number of subsequences of `s[0..i-1]` that match `t[0..j-1]`.
- Base cases:
  - `dp[i][0] = 1` for all `i` (empty string `t` is always a subsequence).
  - `dp[0][j] = 0` for `j > 0` (empty `s` cannot form non-empty `t`).

### Code

```cpp
int numDistinct(string s, string t) {
    int n = s.size(), m = t.size();
    vector<vector<double>> dp(n + 1, vector<double>(m + 1, 0));

    for (int i = 0; i <= n; i++) dp[i][0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i - 1] == t[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    return dp[n][m];
}
```

### Complexity Analysis

**Time Complexity:** `O(n * m)` – We fill an `n × m` dp table.

**Space Complexity:** `O(n * m)` – Table storage.

---

## Space Optimization

- At step `i`, only `i - 1` row is needed.
- Use two arrays: `prev` and `curr`.
- Further optimization: loop `j` backward so we can use just **one array**.

### Code

```cpp
int numDistinct(string s, string t) {
    int n = s.size(), m = t.size();
    vector<long long> dp(m + 1, 0);

    dp[0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= 1; j--) {
            if (s[i - 1] == t[j - 1]) {
                dp[j] = dp[j - 1] + dp[j];
            }
        }
    }
    return dp[m];
}
```

### Complexity Analysis

**Time Complexity:** `O(n * m)` – Each `(i, j)` processed once.

**Space Complexity:** `O(m)` – Only a 1D array of length `m + 1`.

---

THE END
