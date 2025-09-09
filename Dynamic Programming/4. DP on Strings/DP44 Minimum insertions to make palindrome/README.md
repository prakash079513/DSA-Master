# Minimum Insertions to Make a String Palindrome

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

Given a string `s`, return the **minimum number of insertions** needed to make `s` a palindrome.

---

### Editorial

- A palindrome reads the same forward and backward.
- If we know the **longest palindromic subsequence (LPS)** of `s`, then the characters outside this subsequence must be “fixed” (inserted) to form a palindrome.
- Therefore:

  ```
  Minimum Insertions = n – LPS(s)

  ```

  where `n = s.length()`.

So the problem reduces to finding **LPS**.

### Code

```cpp
int minInsertions(string s) {
    int n = s.size();
    vector<int> next(n, 0), curr(n, 0);

    for (int i = n-1; i >= 0; i--) {
        curr[i] = 1;
        for (int j = i+1; j < n; j++) {
            if (s[i] == s[j]) curr[j] = 2 + next[j-1];
            else curr[j] = max(next[j], curr[j-1]);
        }
        next = curr;
    }

    int lps = next[n-1];
    return n - lps;
}
```

### Complexity Analysis

**Time Complexity:** `O(n^2)` – Same as tabulation.

**Space Complexity:** `O(n)` – Only two arrays used.
