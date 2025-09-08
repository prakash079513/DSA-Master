# Longest Palindromic Subsequence

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

Given a string `s`, find the length of the longest subsequence of `s` that is a palindrome.

- A subsequence is derived by deleting some characters (possibly none) without changing the relative order.
- A palindrome reads the same forwards and backwards.

**Example 1:**

```
Input: s = "bbabcbcab"
Output: 7
Explanation: The longest palindromic subsequence is "babcbab".
```

## Editorial

## Recursion

- Let `f(i, j)` = length of the LPS in substring `s[i...j]`.
- Choices:
  1. If `s[i] == s[j]`, then both ends can be included: `2 + f(i+1, j-1)`.
  2. Otherwise, try excluding one end: `max(f(i+1, j), f(i, j-1))`.
- Base cases:
  - If `i > j`, return `0`.
  - If `i == j`, return `1`.

### Code

```cpp
int f(int i, int j, string &s) {
    if (i > j) return 0;
    if (i == j) return 1;

    if (s[i] == s[j]) return 2 + f(i + 1, j - 1, s);

    return max(f(i + 1, j, s), f(i, j - 1, s));
}
```

### Complexity Analysis

**Time Complexity:** `O(2^n)` – At each step(when characters don’t match), we branch into two possibilities. Each mismatch doubles the paths we may explore.

**Space Complexity:** `O(n)` – Recursion depth.

---

## Memoization

- Use a 2D DP array `dp[i][j]` to store results of `f(i, j)`.
- If already computed, return it.

### Code

```cpp
int f(int i, int j, string &s, vector<vector<int>> &dp) {
    if (i > j) return 0;
    if (i == j) return 1;

    if (dp[i][j] != -1) return dp[i][j];

    if (s[i] == s[j]) return dp[i][j] = 2 + f(i + 1, j - 1, s, dp);

    return dp[i][j] = max(f(i + 1, j, s, dp), f(i, j - 1, s, dp));
}
```

### Complexity Analysis

**Time Complexity:** `O(n^2)` – Each state `(i, j)` computed once.

**Space Complexity:** `O(n^2)` – DP table storage + recursion stack.

---

## Tabulation

- Iterative DP with 2D table `dp[n][n]`.
- `dp[i][j]` means LPS length in substring s[i...j].
- So the answer will be in `dp[0][n-1]` (the whole string).

Base case:

- Every single character is a palindrome of length 1. `dp[i][i] = 1` for all i.

Table filling:

- `dp[i][j]` = length of the LPS in substring `s[i...j]`
- To compute `dp[i][j]`, we often need `dp[i+1][j-1]`, `dp[i+1][j]`, or `dp[i][j-1]`. Notice those involve **smaller substrings** than `s[i...j]`.

So if we want `dp[i][j]` for a substring of length `L`, we’d better already know the answers for substrings of length `< L`. That’s why we **fill the table in increasing substring length.**

**Example Walkthrough**

`s = "bbab"` (n=4)

- Step 1: Fill diagonal with 1s (`b`, `b`, `a`, `b`).
- Step 2: Length 2 substrings:
  - `"bb"` → 2
  - `"ba"` → 1
  - `"ab"` → 1
- Step 3: Length 3 substrings:
  - `"bba"` → ends differ, take max inside → 2
  - `"bab"` → ends same → 2 + dp[1][2] = 3
- Step 4: Length 4 substring `"bbab"` → ends differ, so max inside = 3.

Final answer: `dp[0][3] = 3` (`bab`).

### Tabulation for LPS (example `"aba"`)

- **Define:** `dp[i][j] = length of LPS in s[i...j]`

**Length = 1:** single letters → `dp[i][i] = 1`

```
0 1 2
1 . .
. 1 .
. . 1
```

**Length = 2:**

- "ab": ends ≠ → max(1,1) = 1
- "ba": ends ≠ → max(1,1) = 1

```
0 1 2
1 1 .
. 1 1
. . 1
```

**Length = 3:**

- "aba": ends = → 2 + dp[1][1] = 3

```
0 1 2
1 1 3
. 1 1
. . 1
```

**Answer:** `dp[0][n-1] = 3`

### Code

```cpp
int lps(string s) {
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) dp[i][i] = 1;

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (s[i] == s[j]) {
                dp[i][j] = 2 + dp[i + 1][j - 1];
            } else {
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[0][n - 1];
}
```

### Complexity Analysis

**Time Complexity:** `O(n^2)` – Filling an `n x n` table.

**Space Complexity:** `O(n^2)` – 2D DP table.

---

## Space Optimization

- Notice `dp[i][j]` only depends on `dp[i+1][j-1]`, `dp[i+1][j]`, and `dp[i][j-1]`.
- We can optimize by computing row by row (bottom-up from right to left).
- Use 1D array with careful updating.
- Simple: Fill the upper traingle from the last row.

### Code

```cpp
int lps(string s) {
    int n = s.size();
    vector<int> prev(n, 0), curr(n, 0);

    for (int i = n - 1; i >= 0; i--) {
        curr[i] = 1;
        for (int j = i + 1; j < n; j++) {
            if (s[i] == s[j]) {
                curr[j] = 2 + prev[j - 1];
            } else {
                curr[j] = max(prev[j], curr[j - 1]);
            }
        }
        prev = curr;
    }
    return prev[n - 1];
}
```

### Complexity Analysis

**Time Complexity:** `O(n^2)` – Still all pairs considered.

**Space Complexity:** `O(n)` – Only two rows kept.

---

## Using LCS

- Observation: A palindrome reads the same forwards and backwards.
- If we take `s1 = s` and `s2 = reverse(s)`, then the **Longest Common Subsequence (LCS) of s1 and s2** will be the Longest Palindromic Subsequence.

### Steps:

1. Reverse the string `s` to form `rev`.
2. Compute the **LCS(s, rev)**.
3. The LCS length is the answer.

### Code

```cpp
int lps(string s) {
    string rev = s;
    reverse(rev.begin(), rev.end());

    int n = s.size();
    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (s[i-1] == rev[j-1]) {
                dp[i][j] = 1 + dp[i-1][j-1];
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    return dp[n][n];
}
```

### Complexity Analysis

**Time Complexity:** `O(n^2)` – Filling LCS DP table.

**Space Complexity:** `O(n^2)` – For the DP table (can be reduced to `O(n)` with 1D optimization).

---

THE END
