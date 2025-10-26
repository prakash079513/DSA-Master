# Longest Palindrome

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

Given a string **s** containing uppercase and lowercase letters, return the **length** of the longest palindrome that can be built with those characters.

Characters are case-sensitive (A != a).

Constraints:

- `1 ≤ s.length ≤ 2 * 10⁵`
- Contains only English letters

---

## Brute Force Approach

### Approach

- Generate all permutations of the string
- Check which ones are palindromes
- Track the longest length

> (Not feasible but included as brute approach)

### Code (Brute Force) — ❌ Not recommended

```cpp
// Brute force is impractical for this constraint.
// Permutation complexity is factorial, so skipping code.
```

### Complexity Analysis

**Time Complexity:** `O(n!)` — Checking all permutations.
**Space Complexity:** `O(n)` — Recursion and storage.

---

## Expected Optimal Solution (Frequency Counting)

### Approach

- Count frequency of each character
- For each frequency:

  - Add the largest even part to the palindrome
  - If there is any leftover (odd count), track that at least one odd exists

- If any odd count exists → add +1 at the end (for center character)

Example: `aabbccc`

- a → 2, b → 2, c → 3 → even parts = 2+2+2 = 6 → at least one odd → +1 → 7

### Code (Optimal)

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char, int> freq;
        for (char c : s) freq[c]++;

        int length = 0;
        bool oddFound = false;

        for (auto &p : freq) {
            length += (p.second / 2) * 2;
            if (p.second % 2 == 1) oddFound = true;
        }

        return oddFound ? length + 1 : length;
    }
};

int main() {
    string s = "abccccdd";
    Solution sol;
    cout << sol.longestPalindrome(s);
    return 0;
}
```

### Complexity Analysis

**Time Complexity:** `O(n)` — Count characters and sum contributions.
**Space Complexity:** `O(1)` — Frequency map has max 52 buckets (A–Z, a–z).

---

THE END
