## **242. Valid Anagram**

Author: Prakash JC

## Problem Statement

Given two strings `s` and `t`, return **true** if `t` is an **anagram** of `s`, and **false** otherwise.

An anagram is a word formed by rearranging the letters of another word, using all characters exactly once.

---

### Key Takeaway

- Use frequency counting instead of sorting.
- Use an array, s++, t--, if non zero, failed.

---

## Brute Force Approach

### Approach

- Sort both strings
- Compare the sorted strings
- If equal → return true, else false

**Time Complexity:** `O(n log n)`
**Space Complexity:** `O(1)`

## Optimal Approach – Frequency Count

### Key Observation

- Two strings are anagrams if:
  - They have the same length
  - Each character appears the same number of times

- Use an array of size 26 for lowercase letters

### Approach

- If lengths differ → return false
- Create frequency array `freq[26] = {0}`
- Traverse both strings:
  - Increment count for `s[i]`
  - Decrement count for `t[i]`

- After traversal:
  - If all values are 0 → anagram
  - Else → not anagram

## Code

```cpp
bool isAnagram(string s, string t) {
    if (s.size() != t.size()) return false;

    vector<int> freq(26, 0);

    for (int i = 0; i < s.size(); i++) {
        freq[s[i] - 'a']++;
        freq[t[i] - 'a']--;
    }

    for (int i = 0; i < 26; i++) {
        if (freq[i] != 0)
            return false;
    }

    return true;
}
```

---

**Time Complexity:** `O(n)` – single traversal

**Space Complexity:** `O(1)` – fixed size array (26)

---

## Interview Notes

- Frequency method is expected
- Works only for lowercase letters (modify if needed)

---

THE END
