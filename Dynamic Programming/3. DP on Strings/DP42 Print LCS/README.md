# Print Longest Common Subsequence (LCS)

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

Given two strings `s1` and `s2`, print their **Longest Common Subsequence (LCS)**. If multiple subsequences of maximum length exist, printing any one of them is valid.

---

## Editorial

- We first compute the **LCS length** using standard **tabulation DP**.
- Then, we **backtrack** through the DP table to reconstruct the subsequence.

### Approach (Tabulation + Backtracking)

1. **Build the DP table**

   - `dp[i][j]` = length of LCS between `s1[0...i-1]` and `s2[0...j-1]`.
   - Transition:

     If `s1[i-1] == s2[j-1]`:

     ```
     dp[i][j] = 1 + dp[i-1][j-1]
     ```

     Else:

     ```
     dp[i][j] = max(dp[i-1][j], dp[i][j-1])
     ```

2. **Backtracking to construct LCS**
   - Start from `(n, m)` (end of both strings).
   - If characters match → add to answer, move `(i-1, j-1)`.
   - If not → move towards the direction that gave the maximum (`dp[i-1][j]` vs `dp[i][j-1]`).
   - Continue until reaching row `0` or column `0`.
   - Reverse the collected sequence at the end (since we built it backwards).

### Code

```cpp
string printLCS(string s1, string s2) {
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
            i--;
        } else {
            j--;
        }
    }

    reverse(ans.begin(), ans.end());
    return ans;
}
```

---

### Complexity Analysis

**Time Complexity:** `O(n * m)` – filling the DP table and backtracking both take quadratic time.

**Space Complexity:** `O(n * m)` – DP table storage.

---

THE END
