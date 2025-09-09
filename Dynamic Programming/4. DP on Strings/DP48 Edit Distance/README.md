# Edit Distance

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

You are given two strings `s1` and `s2`. You need to transform `s1` into `s2` using the following operations:

1. **Insert** a character
2. **Delete** a character
3. **Replace** a character

Return the **minimum number of operations** required to convert `s1` into `s2`.

---

## Editorial

## Recursion

- Let `i` = index in `s1`, `j` = index in `s2`.
- If `s1[i] == s2[j]`, no operation is needed → recurse on `(i - 1, j - 1)`.
- If `s1[i] != s2[j]`, we have three choices:
  1. **Insert** → match `s1[0..i]` with `s2[0..j-1]`.
  2. **Delete** → match `s1[0..i-1]` with `s2[0..j]`.
  3. **Replace** → match `s1[0..i-1]` with `s2[0..j-1]`.

     Take the **minimum** among them and add `1`.
- Base cases:
  - If `i < 0`, `s1` is empty → need `j + 1` insertions.
  - If `j < 0`, `s2` is empty → need `i + 1` deletions.

### Code

```cpp
int f(int i, int j, string &s1, string &s2) {
    if (i < 0) return j + 1;
    if (j < 0) return i + 1;

    if (s1[i] == s2[j]) return f(i - 1, j - 1, s1, s2);

    int insertOp = 1 + f(i, j - 1, s1, s2);
    int deleteOp = 1 + f(i - 1, j, s1, s2);
    int replaceOp = 1 + f(i - 1, j - 1, s1, s2);

    return min({insertOp, deleteOp, replaceOp});
}
```

### Complexity Analysis

**Time Complexity:** `O(3^n)` – Every mismatch can branch into 3 operations.

**Space Complexity:** `O(n + m)` – Recursion stack.

---

## Memoization

- Use a `dp[i][j]` table where `dp[i][j]` = minimum operations to convert `s1[0..i]` into `s2[0..j]`.
- Store and reuse results.

### Code

```cpp
int f(int i, int j, string &s1, string &s2, vector<vector<int>>& dp) {
    if (i < 0) return j + 1;
    if (j < 0) return i + 1;

    if (dp[i][j] != -1) return dp[i][j];

    if (s1[i] == s2[j]) return dp[i][j] = f(i - 1, j - 1, s1, s2, dp);

    return dp[i][j] = 1 + min({f(i, j-1, s1, s2, dp), f(i-1, j, s1, s2, dp), f(i-1, j-1, s1, s2, dp)});
}
```

### Complexity Analysis

**Time Complexity:** `O(n * m)` – Each state `(i, j)` solved once.

**Space Complexity:** `O(n * m)` for dp + `O(n + m)` recursion stack.

---

## Tabulation

Note: Handle the -1 index case using a table of size n+1 and m+1. Hence decrement the character index by 1 i.e., i+1 becomes i(note the base case ) and i becomes i-1(note the string indexing s[x]).

- `dp[i][j]` = minimum operations to convert `s1[0..i-1]` into `s2[0..j-1]`.

Base cases:

- `dp[0][j] = j` (convert empty `s1` to `s2[0..j-1]` → insert `j` times).
- `dp[i][0] = i` (convert `s1[0..i-1]` to empty `s2` → delete `i` times).

Transition:

- If `s1[i-1] == s2[j-1]`, `dp[i][j] = dp[i-1][j-1]`.
- Else take min among insert, delete, replace.

### Code

```cpp
int minDistance(string s1, string s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min({dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]});
            }
        }
    }
    return dp[n][m];
}
```

### Complexity Analysis

**Time Complexity:** `O(n * m)` – Filling the whole table.

**Space Complexity:** `O(n * m)` – DP table storage.

---

## Space Optimization

- At step `i`, only `i-1` row is needed.
- Use two arrays: `prev` and `curr`.

### Code

```cpp
int minDistance(string s1, string s2) {
    int n = s1.size(), m = s2.size();
    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    for (int j = 0; j <= m; j++) prev[j] = j;

    for (int i = 1; i <= n; i++) {
        curr[0] = i;
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                curr[j] = prev[j - 1];
            } else {
                curr[j] = 1 + min({curr[j - 1], prev[j], prev[j - 1]});
            }
        }
        prev = curr;
    }
    return prev[m];
}
```

### Complexity Analysis

**Time Complexity:** `O(n * m)` – Same work as tabulation.

**Space Complexity:** `O(m)` – Only two rows needed.

---

THE END
