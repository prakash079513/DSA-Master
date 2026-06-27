## **383. Ransom Note**

Author: Prakash JC

## Problem Statement

Given two strings `ransomNote` and `magazine`, return **true** if `ransomNote` can be constructed using the letters from `magazine`, otherwise return **false**.

Each letter in `magazine` can only be used **once**.

---

### Key Takeaway

- Use frequency counting to ensure magazine has enough characters.
- Count freq for magazine, loop over the ransomnote chars, if non zero freq, return false.

---

## Brute Force Approach

### Approach

- For each character in `ransomNote`
  - Search for it in `magazine`
  - If found, remove that character from `magazine`
  - If not found → return false

- If all characters are matched → return true

**Time Complexity:** `O(n * m)`

**Space Complexity:** `O(1)`

## Optimal Approach – Frequency Count

### Key Observation

- We only care about availability of characters
- Order does not matter
- Count frequency of characters in `magazine`

### Approach

- Create frequency array `freq[26] = {0}`
- Traverse `magazine` and fill frequencies
- Traverse `ransomNote`:
  - If frequency of character is 0 → return false
  - Else decrement frequency

- If all characters matched → return true

## Code

```cpp id="nq6g5v"
bool canConstruct(string ransomNote, string magazine) {
    vector<int> freq(26, 0);

    for (int i = 0; i < magazine.size(); i++) {
        freq[magazine[i] - 'a']++;
    }

    for (int i = 0; i < ransomNote.size(); i++) {
        if (freq[ransomNote[i] - 'a'] == 0)
            return false;

        freq[ransomNote[i] - 'a']--;
    }

    return true;
}
```

---

**Time Complexity:** `O(n + m)` – O(n) + O(m).

**Space Complexity:** `O(1)` – fixed size array (26)

## Interview Notes

- Do **not** sort → unnecessary
- Frequency counting is optimal
- Note down the resource, if it's not there in the resource, return false.

---

THE END
