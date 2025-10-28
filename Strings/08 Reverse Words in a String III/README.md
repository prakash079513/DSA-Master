# Reverse Words in a String III

Author: [Prakash JC](https://prakash079513.github.io/)

## Problem Statement

Given a string `s` consisting of words separated by **single spaces**,

reverse the characters of each word in place, **keeping the order of words the same**.

Example:

Input: `"Let's take LeetCode contest"`

Output: `"s'teL ekat edoCteeL tsetnoc"`

Constraints:

- `1 ≤ s.length ≤ 5 * 10⁴`
- Only printable ASCII characters
- Words separated by one space, no leading/trailing spaces

---

## Brute Force Approach

### Approach

- Use stringstream to split into words
- Reverse each word individually
- Append reversed words with space

### Code (Brute Force)

```cpp
string reverseWords(string s) {
    stringstream ss(s);
    string word, ans;

    while (ss >> word) {
        reverse(word.begin(), word.end());
        ans += word + " ";
    }

    ans.pop_back(); // remove last space
    return ans;
}
```

### Complexity Analysis

**Time Complexity:** `O(n)` — reverse each character once

**Space Complexity:** `O(n)` — new string and extracted words

---

## Expected Optimal Solution (In-Place Two Pointer)

### Approach

- Traverse the string
- Track word start index
- When hitting a space or end of string → reverse that word in place

### Code (Optimal)

```cpp
string reverseWords(string s) {
    int n = s.size();
    int start = 0;

    for (int i = 0; i <= n; i++) {
        if (i == n || s[i] == ' ') {
            reverse(s.begin() + start, s.begin() + i);
            start = i + 1;
        }
    }
    return s;
}
```

### Complexity Analysis

**Time Complexity:** `O(n)` — each character reversed once

**Space Complexity:** `O(1)` — in-place operations.

---

THE END
