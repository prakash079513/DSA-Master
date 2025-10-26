# Valid Palindrome

Author: [Prakash JC](https://prakash079513.github.io/)

## Problem Statement

Given a string **s**, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

Constraints:

- `1 ≤ s.length ≤ 2 * 10⁵`
- Contains ASCII printable characters

---

## Brute Force Approach

### Approach

- Traverse string
- Keep only alphanumeric characters and convert to lowercase
- Check if the resulting string is equal to its reverse

### Code (Brute Force)

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        string t = "";
        for (char c : s) {
            if (isalnum(c)) t += tolower(c);
        }
        string r = t;
        reverse(r.begin(), r.end());
        return t == r;
    }
};

int main() {
    string s = "A man, a plan, a canal: Panama";
    Solution sol;
    cout << sol.isPalindrome(s);
    return 0;
}
```

### Complexity Analysis

**Time Complexity:** `O(n)` — Filtering and comparing whole string.

**Space Complexity:** `O(n)` — Extra string storing filtered characters.

---

## Expected Optimal Solution (Two-Pointer)

### Approach

- Use two pointers: `left` at start and `right` at end
- Move pointers inward, skipping non-alphanumeric characters
- Compare lowercase versions of valid characters
- If mismatch → return false
- At the end → return true

### Code (Optimal)

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        int left = 0, right = s.size() - 1;

        while (left < right) {
            if (!isalnum(s[left])) { left++; continue; }
            if (!isalnum(s[right])) { right--; continue; }

            if (tolower(s[left]) != tolower(s[right])) return false;

            left++;
            right--;
        }
        return true;
    }
};

int main() {
    string s = "A man, a plan, a canal: Panama";
    Solution sol;
    cout << sol.isPalindrome(s);
    return 0;
}
```

### Complexity Analysis

**Time Complexity:** `O(n)` — Single scan with two pointers.

**Space Complexity:** `O(1)` — No extra string created.

---

THE END
