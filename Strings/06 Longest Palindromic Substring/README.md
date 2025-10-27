# Longest Palindromic Substring

Author: [Prakash JC](https://prakash079513.github.io/)

## Problem Statement

Given a string **s**, return the **longest palindromic substring** in **s**.

Constraints:

- `1 ≤ s.length ≤ 1000`
- Contains only English letters and digits

---

## Brute Force Approach

### Approach

- Generate all possible substrings
- Check each substring if it is palindrome
- Track the longest palindrome found

### Code (Brute Force)

```cpp
bool isPal(string &s, int i, int j) {
    while (i < j) {
        if (s[i] != s[j]) return false;
        i++; j--;
    }
    return true;
}

string longestPalindrome(string s) {
    int n = s.size();
    string ans = "";
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (isPal(s, i, j) && (j - i + 1) > ans.size()) {
                ans = s.substr(i, j - i + 1);
            }
        }
    }
    return ans;
}
```

### Complexity Analysis

**Time Complexity:** `O(n³)` — Generate substrings + palindrome check for each.

**Space Complexity:** `O(1)` — Only storing result.

---

## Expected Optimal Solution (Expand Around Center)

### Approach

- A palindrome expands from the center
- There are **2n−1 centers**:
  - n odd-length centers (single char)
  - n−1 even-length centers (between two chars)
- Expand from each center and track longest palindrome

Example:

- For center at index `i` → expand left & right while characters match

### Code (Optimal)

```cpp
string longestPalindrome(string s) {
    int n = s.size();
    int start = 0, maxLen = 1;

    auto expand = [&](int left, int right) {
        while (left >= 0 && right < n && s[left] == s[right]) {
            if (right - left + 1 > maxLen) {
                start = left;
                maxLen = right - left + 1;
            }
            left--;
            right++;
        }
    };

    for (int i = 0; i < n; i++) {
        expand(i, i);     // Odd length
        expand(i, i + 1); // Even length
    }

    return s.substr(start, maxLen);
}
```

### Refactored Code

```cpp
string longestPalindrome(string s) {
    int n = s.size();
    int start = 0, maxLen = 1;

    for (int i = 0; i < n; i++) {
        expand(s, n, i, i, start, maxLen);     // Odd length
        expand(s, n, i, i + 1, start, maxLen); // Even length
    }

    return s.substr(start, maxLen);
}

void expand(const string &s, int n, int left, int right, int &start, int &maxLen) {
    while (left >= 0 && right < n && s[left] == s[right]) {
        if (right - left + 1 > maxLen) {
            start = left;
            maxLen = right - left + 1;
        }
        left--;
        right++;
    }
}
```

### Complexity Analysis

**Time Complexity:** `O(n²)` — Each center expansion worst case scans entire string.

**Space Complexity:** `O(1)` — Just tracking indices and lengths.

---

THE END
