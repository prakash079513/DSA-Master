# Minimum Insertions and Deletions to Make str1 equals to str2

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

Given two strings `s1` and `s2`, return the **minimum number of insertions and deletions** required to make `s1` equal to `s2`.

---

## Editorial Overview

- To transform `s1` into `s2`, we care about the **Longest Common Subsequence (LCS)**.
- LCS is the part of the string we can keep (no insert/delete needed).
- Characters not in LCS must be deleted from `s1` or inserted into `s1` to match `s2`.

Formulas:

```
Deletions = |s1| – LCS(s1, s2)
Insertions = |s2| – LCS(s1, s2)
Answer = Deletions + Insertions

```

So the heart of the problem is computing **LCS**.

---

## Space Optimization

### Code

```cpp
int minInsDel(string s1, string s2) {
    int n1 = s1.size(), n2 = s2.size();
    vector<int> prev(n2+1, 0), curr(n2+1, 0);

    for (int i = 1; i <= n1; i++) {
        for (int j = 1; j <= n2; j++) {
            if (s1[i-1] == s2[j-1])
                curr[j] = 1 + prev[j-1];
            else
                curr[j] = max(prev[j], curr[j-1]);
        }
        prev = curr;
    }

    int lcs = prev[n2];
    return (n1 - lcs) + (n2 - lcs);
}
```

### Complexity Analysis

**Time Complexity:** `O(n1 * n2)` – same as tabulation.

**Space Complexity:** `O(n2)` – only two rows needed.

---

THE END
