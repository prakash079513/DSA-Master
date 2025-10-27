# Valid Anagram

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

You are given two strings **s** and **t**.

Return **true** if **t** is an anagram of **s**, else return **false**.

(An anagram rearranges characters but keeps counts the same.)

Constraints:

- Only lowercase English letters (for this version of the problem)
- `1 ≤ s.length, t.length ≤ 5 * 10⁴`

---

## Brute Force Approach

### Approach

- If lengths differ → return false immediately
- Sort both strings
- Compare sorted results

### Code (Brute Force)

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) return false;
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return s == t;
    }
};

int main() {
    string s = "anagram", t = "nagaram";
    Solution sol;
    cout << sol.isAnagram(s, t);
    return 0;
}
```

### Complexity Analysis

**Time Complexity:** `O(n log n)` — Sorting takes dominant time.

**Space Complexity:** `O(1)` — Sorting in-place (ignoring sort internal stack).

---

## Expected Optimal Solution (Hash Counting)

### Approach

- Frequency count using array of size 26
- Increment for each char in `s`, decrement for each char in `t`
- If all counts end as 0 → valid anagram

### Code (Optimal)

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) return false;
        int freq[26] = {0};

        for (char c : s) freq[c - 'a']++;
        for (char c : t) freq[c - 'a']--;

        for (int i = 0; i < 26; i++) {
            if (freq[i] != 0) return false;
        }
        return true;
    }
};

int main() {
    string s = "anagram", t = "nagaram";
    Solution sol;
    cout << sol.isAnagram(s, t);
    return 0;
}
```

### Complexity Analysis

**Time Complexity:** `O(n)` — Single frequency pass.

**Space Complexity:** `O(1)` — Fixed 26-length frequency array.

---

THE END
