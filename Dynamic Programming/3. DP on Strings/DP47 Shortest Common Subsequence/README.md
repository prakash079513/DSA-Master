# Shortest Common Supersequence (SCS)

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

Given two strings `s1` and `s2`, return their **Shortest Common Supersequence (SCS)** — the shortest string that contains both `s1` and `s2` as subsequences.

---

## Editorial

- The **LCS (Longest Common Subsequence)** acts as the backbone for solving this problem.
- **Key Insight:** The **SCS length = n + m – LCS length**, but printing requires actual backtracking.
- Idea:
  - Wherever characters match (part of LCS), include them only once in the result.
  - Wherever they differ, include all non-matching characters.
- Using **tabulation + backtracking**, we first compute LCS, then build the SCS from both strings by merging them while respecting the LCS.

---

### Approach (Tabulation + Backtracking)

**Compute LCS DP Table**

- Build `dp[i][j]` same as LCS:

  If `s1[i-1] == s2[j-1]`:
  `   dp[i][j] = 1 + dp[i-1][j-1]`

  Else:
  `   dp[i][j] = max(dp[i-1][j], dp[i][j-1])`

**Backtrack to construct SCS**

- Start from `(n, m)`.
- If `s1[i-1] == s2[j-1]` → add that char once, move `(i-1, j-1)`.
- If not equal → move towards the bigger of `dp[i-1][j]` vs `dp[i][j-1]`.
  - If moving up (take from `s1`) → add `s1[i-1]`.
  - If moving left (take from `s2`) → add `s2[j-1]`.
- Continue until one string is exhausted.
- Add remaining characters of the unfinished string.
- Reverse at the end (since we built backward).

### Code

```cpp
string scs(string s1, string s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i-1] == s2[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }

    int i = n, j = m;
    string ans = "";
    while (i > 0 && j > 0) {
        if (s1[i-1] == s2[j-1]) {
            ans.push_back(s1[i-1]);
            i--; j--;
        } else if (dp[i-1][j] > dp[i][j-1]) {
            ans.push_back(s1[i-1]);
            i--;
        } else {
            ans.push_back(s2[j-1]);
            j--;
        }
    }

    // Add remaining characters
    while (i > 0) {
        ans.push_back(s1[i-1]);
        i--;
    }
    while (j > 0) {
        ans.push_back(s2[j-1]);
        j--;
    }

    reverse(ans.begin(), ans.end());
    return ans;
}
```

---

### Complexity Analysis

**Time Complexity:** `O(n * m)` – Filling DP + Backtracking.

**Space Complexity:** `O(n * m)` – Storing DP table.

---

THE END
