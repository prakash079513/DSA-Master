# Minimum Window Substring

Author: [Prakash JC](https://prakash079513.github.io/)

## Problem Statement

Given two strings `s` and `t`, return the **minimum window substring** of `s` such that **every character** in `t` (including frequency) is included in the window.

If no such substring exists, return `""`.

Example:

Input: `s = "ADOBECODEBANC", t = "ABC"`

Output: `"BANC"`

Constraints:

- `1 ≤ s.length, t.length ≤ 10⁵`
- Characters include ASCII set

---

## Brute Force Approach

### Approach

- For every possible substring of `s`:
  - Check if it contains all characters of `t` with correct count
- Track minimum valid length

Works for very small input but Too slow for constraints

### Code (Brute Force)

```cpp
string minWindow(string s, string t) {
    if (t.size() > s.size()) return "";

    int n = s.size();
    string ans = "";
    int minLen = INT_MAX;

    unordered_map<char, int> freqT;
    for (char c : t) freqT[c]++;

    for (int i = 0; i < n; i++) {
        unordered_map<char, int> freq;
        for (int j = i; j < n; j++) {
            freq[s[j]]++;
            bool valid = true;
            for (auto &p : freqT) {
                if (freq[p.first] < p.second) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                if (j - i + 1 < minLen) {
                    minLen = j - i + 1;
                    ans = s.substr(i, minLen);
                }
                break;
            }
        }
    }
    return ans;
}
```

### Complexity Analysis

**Time Complexity:** `O(n² * charset)` — checking all substrings

**Space Complexity:** `O(charset)` — frequency maps

---

## Expected Optimal Solution (Sliding Window + Two Maps)

### Approach

- Use hashmap `need[]` to count required characters of `t`
- Expand window using right pointer to include necessary chars
- Maintain `formed` count when a requirement is fully satisfied
- When all characters satisfied:
  - Try shrinking from left to minimize window
- Update best window length when valid

This keeps window always valid and minimal possible.

### Code (Optimal)

```cpp
string minWindow(string s, string t) {
    if (t.size() > s.size()) return "";

    vector<int> need(128, 0);
    for (char c : t) need[c]++;

    int required = t.size();
    int left = 0, minLen = INT_MAX, start = 0;

    for (int right = 0; right < s.size(); right++) {
        if (need[s[right]] > 0) required--;
        need[s[right]]--;

        while (required == 0) {
            if (right - left + 1 < minLen) {
                minLen = right - left + 1;
                start = left;
            }
            need[s[left]]++;
            if (need[s[left]] > 0) required++;
            left++;
        }
    }
    return minLen == INT_MAX ? "" : s.substr(start, minLen);
}
```

### Complexity Analysis

**Time Complexity:** `O(n)` — each pointer moves at most `n` times

**Space Complexity:** `O(charset)` — ASCII array (128 fixed)

---

THE END
