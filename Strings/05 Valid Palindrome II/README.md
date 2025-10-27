# Valid Palindrome II

Author: [Prakash JC](https://prakash079513.github.io/)

## Problem Statement

Given a string **s**, return **true** if the string can become a palindrome after deleting **at most one** character.

Constraints:

- `1 ≤ s.length ≤ 10⁵`
- Contains only lowercase English letters

---

## Brute Force Approach

### Approach

- Try removing each character one by one
- Check if the remaining string is palindrome
- If any removal results in a palindrome → return true
- If none work → return false

### Code (Brute Force)

```cpp
bool isPal(string &s, int i, int j) {
    while (i < j) {
        if (s[i] != s[j]) return false;
        i++; j--;
    }
    return true;
}

bool validPalindrome(string s) {
    int n = s.size();
    for (int i = 0; i < n; i++) {
        string t = s.substr(0, i) + s.substr(i + 1);
        if (isPal(t, 0, t.size() - 1)) return true;
    }
    return isPal(s, 0, n - 1);
}
```

### Complexity Analysis

**Time Complexity:** `O(n²)` — Each index removal creates a substring and validates.

**Space Complexity:** `O(n)` — Substring creation.

---

## Expected Optimal Solution (Two-Pointer)

### Approach

- Check palindrome normally using two pointers
- When a mismatch occurs:
  - Either skip the left character
  - Or skip the right character
- Check if either resulting substring is palindrome
- If yes → valid with one deletion allowed

### Code (Optimal)

```cpp
bool isPal(string &s, int i, int j) {
    while (i < j) {
        if (s[i] != s[j]) return false;
        i++; j--;
    }
    return true;
}

bool validPalindrome(string s) {
    int left = 0, right = s.size() - 1;

    while (left < right) {
        if (s[left] != s[right]) {
            return isPal(s, left + 1, right) || isPal(s, left, right - 1);
        }
        left++;
        right--;
    }
    return true;
}
```

### Complexity Analysis

**Time Complexity:** `O(n)` — One scan and up to two quick checks.

**Space Complexity:** `O(1)` — No extra storage.

---

THE END
