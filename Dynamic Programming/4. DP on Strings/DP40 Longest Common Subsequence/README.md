# Longest Common Subsequence (LCS)

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

Given two strings `s1` of length `m` and `s2` of length `n`, find the length of their **Longest Common Subsequence** (LCS).

A subsequence is a sequence derived from another string by deleting some characters without changing the order of the remaining characters.

Example:

`s1 = "abcde"`, `s2 = "ace"` → LCS = `"ace"`, length = 3.

---

## Editorial

## Recursion

- Think recursively: at each index `(i, j)` in strings `s1` and `s2`.
- If `s1[i] == s2[j]`, then that character is part of LCS → `1 + f(i-1, j-1)`.
- Otherwise, we explore both options: skip from `s1` or skip from `s2`.
- Base case: if either index is below 0, return 0.

### Evolving Thought Process

1. Start from the end of both strings (`i = m-1, j = n-1`).
2. If last chars match → include + move diagonally.
3. If not → try excluding from either string and take max.

### Code

```cpp

int f(int i, int j, string &s1, string &s2) {
    if(i < 0 || j < 0) return 0;
    if(s1[i] == s2[j]) return 1 + f(i-1, j-1, s1, s2);
    return max(f(i-1, j, s1, s2), f(i, j-1, s1, s2));
}
```

### Complexity Analysis

**Time Complexity:** `O(2^(m*n))` – every pair `(i,j)` can branch two ways.

**Space Complexity:** `O(m+n)` – recursion stack depth.

---

## Memoization

- Use a 2D DP array `dp[m][n]` where `dp[i][j]` stores the LCS length for `s1[0..i]` and `s2[0..j]`.
- Avoids recomputation by caching recursive results.

### Code

```cpp
int f(int i, int j, string &s1, string &s2, vector<vector<int>> &dp) {
    if(i < 0 || j < 0) return 0;
    if(dp[i][j] != -1) return dp[i][j];

    if(s1[i] == s2[j])
        return dp[i][j] = 1 + f(i-1, j-1, s1, s2, dp);

    return dp[i][j] = max(f(i-1, j, s1, s2, dp), f(i, j-1, s1, s2, dp));
}
```

### Complexity Analysis

**Time Complexity:** `O(m*n)` – each state `(i,j)` solved once.

**Space Complexity:** `O(m*n) + O(m+n)` – DP table + recursion stack.

---

## Tabulation

- Iterative bottom-up DP.
- Define `dp[i][j]` = LCS of first `i` chars of `s1` and first `j` chars of `s2`.
- Transition:
  - If `s1[i-1] == s2[j-1]` → `dp[i][j] = 1 + dp[i-1][j-1]`.
  - Else → `dp[i][j] = max(dp[i-1][j], dp[i][j-1])`.
- Answer = `dp[m][n]`.

### Code

```cpp
int longestCommonSubsequence(string s1, string s2) {
		int m = s1.size(), n = s2.size();
		vector<vector<int>> dp(m+1, vector<int>(n+1, 0));

		for(int i=1; i<=m; i++) {
		    for(int j=1; j<=n; j++) {
		        if(s1[i-1] == s2[j-1])
		            dp[i][j] = 1 + dp[i-1][j-1];
		        else
		            dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
		    }
		}
		return dp[m][n];
}
```

### Complexity Analysis

**Time Complexity:** `O(m*n)` – filling table.

**Space Complexity:** `O(m*n)` – DP table.

---

## Space Optimization

- Only previous row and current row are needed.
- Reduce 2D DP to 2 arrays of size `n+1`.

### Code

```cpp
int longestCommonSubsequence(string s1, string s2) {
    int m = s1.size(), n = s2.size();
    vector<int> prev(n+1, 0), curr(n+1, 0);

    for(int i=1; i<=m; i++) {
        for(int j=1; j<=n; j++) {
            if(s1[i-1] == s2[j-1])
                curr[j] = 1 + prev[j-1];
            else
                curr[j] = max(prev[j], curr[j-1]);
        }
        prev = curr;
    }
    return prev[n];
}
```

### Complexity Analysis

**Time Complexity:** `O(m*n)` – nested loops.

**Space Complexity:** `O(n)` – only two rows stored.

---

THE END
