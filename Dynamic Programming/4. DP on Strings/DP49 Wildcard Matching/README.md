# Wildcard Matching

Author: [Prakash JC](https://prakash079513.github.io/)

## Problem Statement

You are given two strings:

- `s` → the input string (e.g., `"asdfasdfasdfsdf"`)
- `p` → the pattern (e.g., `"abc*asdf"`)

The pattern may contain two wildcards:

- `?` → matches exactly **one** character
- `*` → matches **zero or more** characters

Return `true` if the entire string `s` matches the pattern `p`.

---

## Editorial

## Recursion

- Let `i` = index in the pattern `p`
- Let `j` = index in the string `s`

**Define:**

- `f(n-1, m-1)` tells whether we can match the pattern `p` from `0` till `i` with the string `s` from `0` till `j`.

**Cases:**

1. If `p[i] == s[j]` or `p[i] == '?'`: recurse `(i-1, j-1)`.
2. If `p[i] == '*'`: Think recursively:

   - Treat `*` as matching **zero characters** → `(i-1, j)`
   - Or `*` matches **one more character** → `(i, j-1)`

   Note: This way for their next calls we have multiple characters under `*`.

3. **Note:** If there is no `?` or `*` at the current index yet the characters dont match: return `false`.

**Base cases:**

- If `i < 0` and `j < 0`: both consumed: return `true`
- If `i < 0` and `j >= 0`: pattern empty, string not: return `false`
- If `j < 0` and `i >= 0`: string empty, pattern not:
  - Check if all remaining pattern characters are `*`. Only then return `true`.

### Code

```cpp
bool f(int i, int j, string &p, string &s) {
    if (i < 0 && j < 0) return true;
    if (i < 0 && j >= 0) return false;
    if (j < 0 && i >= 0) {
        for (int k = 0; k <= i; k++) {
            if (p[k] != '*') return false;
        }
        return true;
    }

    if (p[i] == s[j] || p[i] == '?') return f(i - 1, j - 1, p, s);
    if (p[i] == '*') return f(i - 1, j, p, s) || f(i, j - 1, p, s);

    return false;
}
```

### Complexity Analysis

**Time Complexity:** `O(2^(n+m))` – In the worst case, for every `*` we branch into two recursive calls. With many `*` and long string/pattern lengths, this grows exponentially.

**Space Complexity:** `O(n+m)` – Maximum depth of recursion stack.

---

## Memoization

We add a `dp[i][j]` table where `dp[i][j]` stores whether `p[0..i]` matches `s[0..j]`.

### Code

```cpp
bool f(int i, int j, string &p, string &s, vector<vector<int>>& dp) {
    if (i < 0 && j < 0) return true;
    if (i < 0 && j >= 0) return false;
    if (j < 0 && i >= 0) {
        for (int k = 0; k <= i; k++) {
            if (p[k] != '*') return false;
        }
        return true;
    }

    if (dp[i][j] != -1) return dp[i][j];

    if (p[i] == s[j] || p[i] == '?')
        return dp[i][j] = f(i - 1, j - 1, p, s, dp);
    if (p[i] == '*')
        return dp[i][j] = f(i - 1, j, p, s, dp) || f(i, j - 1, p, s, dp);

    return dp[i][j] = false;
}
```

### Complexity Analysis

**Time Complexity:** `O(n * m)` – Each state `(i, j)` is computed at most once.

**Space Complexity:** `O(n * m)` + `O(n+m)`

---

## Tabulation

Fill a `dp` table iteratively.

Handle the `-1` index case:

- `dp[i][j]` = does `p[0..i-1]` match `s[0..j-1]`.

**Base cases:**

- `dp[0][0] = true` (empty pattern matches empty string).
- `dp[i][0] = true` if and only if all `p[0..i-1]` are `*`.
- `dp[0][j] = false` for `j > 0` (empty pattern can’t match non-empty string).

**Transition:**

- If `p[i-1] == s[j-1]` or `p[i-1] == '?'`: `dp[i][j] = dp[i-1][j-1]`
- If `p[i-1] == '*'`: `dp[i][j] = dp[i-1][j] || dp[i][j-1]`

### Code

```cpp
bool isMatch(string s, string p) {
    int n = s.size(), m = p.size();
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));

    dp[0][0] = true;

    for (int i = 1; i <= m; i++) {
        bool allStar = true;
        for (int k = 1; k <= i; k++) {
            if (p[k - 1] != '*') { allStar = false; break; }
        }
        dp[i][0] = allStar;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (p[i - 1] == s[j - 1] || p[i - 1] == '?') {
                dp[i][j] = dp[i - 1][j - 1];
            } else if (p[i - 1] == '*') {
                dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
            }
        }
    }
    return dp[m][n];
}
```

### Complexity Analysis

**Time Complexity:** `O(n * m)` – Two nested loops.

**Space Complexity:** `O(n * m)` – Full DP table.

---

## Space Optimization (1D)

Since each row `i` only depends on row `i-1` and the current row itself (for `*` case), we can use **two 1D arrays**: `prev` and `curr`.

### Code

```cpp
bool isMatch(string s, string p) {
    int n = s.size(), m = p.size();
    vector<bool> prev(n + 1, false), curr(n + 1, false);

    prev[0] = true;

    for (int i = 1; i <= m; i++) {
        curr[0] = true;
        for (int k = 1; k <= i; k++) {
            if (p[k - 1] != '*') { curr[0] = false; break; }
        }

        for (int j = 1; j <= n; j++) {
            if (p[i - 1] == s[j - 1] || p[i - 1] == '?') {
                curr[j] = prev[j - 1];
            } else if (p[i - 1] == '*') {
                curr[j] = prev[j] || curr[j - 1];
            } else {
                curr[j] = false;
            }
        }
        prev = curr;
    }
    return prev[n];
}
```

---

## Complexity Analysis

**Time Complexity:** `O(n * m)` – each pattern vs string position computed once.

**Space Complexity:** `O(n)` – after 1D optimization.

---

THE END
