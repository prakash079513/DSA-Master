# Longest Substring Without Repeating Characters

Author: [Prakash JC](https://prakash079513.github.io/)

## Problem Statement

Given a string `s`, return the length of the **longest substring** without repeating characters.

A substring is a **contiguous** part of the string.

Example:

Input: `s = "abcabcbb"`

Output: `3`

Explanation: `"abc"` is longest without repeating.

Constraints:

- `0 ≤ s.length ≤ 5 * 10⁴`
- Characters include ASCII set

---

## Brute Force Approach

### Approach

- Generate all substrings
- Check if substring has repeated chars using a set
- Track the maximum valid length

### Code (Brute Force)

```cpp
int lengthOfLongestSubstring(string s) {
    int n = s.size();
    int ans = 0;

    for (int i = 0; i < n; i++) {
        unordered_set<char> st;
        for (int j = i; j < n; j++) {
            if (st.count(s[j])) break;
            st.insert(s[j]);
            ans = max(ans, j - i + 1);
        }
    }
    return ans;
}
```

### Complexity Analysis

**Time Complexity:** `O(n²)` — nested loops generate substrings

**Space Complexity:** `O(min(n, charset))` — set for substring check

---

## Expected Optimal Solution (Sliding Window + Hashing)

### Approach

- Maintain a sliding window `[left → right]`
- Use a hashmap to store last seen index of each character
- When a character repeats:
  - Move `left` to `max(left, last_seen[char] + 1)`
- Update max length continuously

This ensures no repetition inside the window.

### Code (Optimal)

```cpp
int lengthOfLongestSubstring(string s) {
    vector<int> last(256, -1);
    int left = 0, ans = 0;

    for (int right = 0; right < s.size(); right++) {
        if (last[s[right]] != -1) {
            left = max(left, last[s[right]] + 1);
        }
        last[s[right]] = right;
        ans = max(ans, right - left + 1);
    }
    return ans;
}
```

### Complexity Analysis

**Time Complexity:** `O(n)` — each pointer moves once

**Space Complexity:** `O(1)` — fixed size array for ASCII (256 entries)

---

THE END
