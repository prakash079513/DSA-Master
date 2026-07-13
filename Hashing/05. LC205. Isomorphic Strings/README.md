## **205. Isomorphic Strings**

Author: Prakash JC

## Problem Statement

Given two strings `s` and `t`, determine if they are **isomorphic**.

Two strings are isomorphic if:

- Each character in `s` maps to exactly one character in `t`
- No two different characters map to the same character
- Mapping must be **consistent**

### Key Takeaway

- enforce **bijection** → one-to-one and consistent mapping in both directions.

---

## Brute Force Approach

### Approach

- Compare every pair `(i, j)`
- If `s[i] == s[j]` → `t[i]` must equal `t[j]`
- If `s[i] != s[j]` → `t[i]` must not equal `t[j]`
- If any condition fails → return false

**Time Complexity:** `O(n^2)`

**Space Complexity:** `O(1)`

## Code (Brute Force)

```cpp
bool isIsomorphic(string s, string t) {
    int n = s.length();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {

            if (s[i] == s[j] && t[i] != t[j])
                return false;

            if (s[i] != s[j] && t[i] == t[j])
                return false;
        }
    }
    return true;
}
```

## Approach 2 – Single Map + Inner Loop

### Key Observation

- Maintain mapping `s → t`
- Must also ensure no two characters map to same target
- Inner loop checks if target is already used

### Approach

- Use array `mapST[256]`
- If no mapping:
  - Check if `t[i]` already mapped (inner loop)

- Else:
  - Check consistency

## Code

```cpp
bool isIsomorphic(string s, string t) {
    if (s.length() != t.length()) return false;

    vector<char> mapST(256, 0);

    for (int i = 0; i < s.length(); i++) {
        char c1 = s[i];
        char c2 = t[i];

        if (mapST[c1] == 0) {
            for (int j = 0; j < 256; j++) {
                if (mapST[j] == c2)
                    return false;
            }
            mapST[c1] = c2;
        } else {
            if (mapST[c1] != c2)
                return false;
        }
    }
    return true;
}
```

## Approach 3 – Two Arrays (Optimal, No Inner Loop)

### Key Observation

- Use two mappings:
  - `s → t`
  - `t → s`

- This ensures **bijection**
- Removes need for inner loop

---

### Common Mistake (Very Important)

- Wrong logic:
  - If both `mapST[c1]` and `mapTS[c2]` are already filled → return false

- Why wrong?
  - Already mapped does **not mean invalid**
  - It is valid **if mapping is consistent**

Correct logic:

- If already mapped → **check consistency**
- Only return false if mismatch occurs

---

### Approach

- Create two arrays:
  - `mapST[256] = -1`
  - `mapTS[256] = -1`

- Traverse:
  - If both unmapped → assign mapping
  - Else:
    - Check if `mapST[c1] == c2` AND `mapTS[c2] == c1`
    - If not → return false

---

### Note on 256 Size

- `256` represents all possible **ASCII characters**
- `arr[char]` means:
  - character is automatically converted to its ASCII value
  - so indexing is like `arr[ASCII value]`

Example:

- `'a' → 97`
- So `arr['a']` = `arr[97]`

## Code (Optimal)

```cpp
bool isIsomorphic(string s, string t) {
    if (s.length() != t.length()) return false;

    vector<int> mapST(256, -1);
    vector<int> mapTS(256, -1);

    for (int i = 0; i < s.length(); i++) {
        char c1 = s[i];
        char c2 = t[i];

        if (mapST[c1] == -1 && mapTS[c2] == -1) {
            mapST[c1] = c2;
            mapTS[c2] = c1;
        } else {
            if (mapST[c1] != c2 || mapTS[c2] != c1)
                return false;
        }
    }
    return true;
}
```

---

**Time Complexity:** `O(n)` – single traversal

**Space Complexity:** `O(1)` – fixed size arrays

## Interview Notes

- Core idea = **bijection**
- Do not confuse “already mapped” with “invalid”
- Always check **consistency before rejecting**
- 2-array method is the **cleanest and expected solution**

---

THE END
