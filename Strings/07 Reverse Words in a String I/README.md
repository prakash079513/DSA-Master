# Reverse Words in a String I

Author: [Prakash JC](https://prakash079513.github.io/)

## Problem Statement

Given a string **s**, reverse the order of the words.

- A word is defined as a sequence of non-space characters
- Multiple spaces may exist between words
- Remove leading/trailing/multiple spaces in the output

Return the reordered string.

Constraints:

- `1 ≤ s.length ≤ 10⁵`
- Contains ASCII characters

---

## Brute Force Approach

### Approach

- Split the string by spaces to get all tokens
- Filter out empty tokens (caused by extra spaces)
- Reverse the vector of words
- Join them with a single space

### Code (Brute Force)

```cpp
string reverseWords(string s) {
    stringstream ss(s);
    string word;
    vector<string> words;

    while (ss >> word) words.push_back(word); // auto trims spaces

    reverse(words.begin(), words.end());

    string ans = "";
    for (int i = 0; i < words.size(); i++) {
        if (i) ans += " ";
        ans += words[i];
    }
    return ans;
}
```

### Complexity Analysis

**Time Complexity:** `O(n)` — Single pass split + reverse

**Space Complexity:** `O(n)` — Stores all words

---

## Expected Optimal Solution (In-Place Manipulation)

### Approach

- Trim leading and trailing spaces
- Reverse the whole string
- Ensure only one space exists between words
- Reverse each word back to correct order inside

Example:

Input → `"  hello   world  "`

Trim → `"hello   world"`

Reverse whole → `"dlrow   olleh"`

Reverse each word → `"world hello"`

### Code (Optimal)

```cpp
string reverseWords(string s) {
    // Step 1: Trim leading and trailing spaces
    int n = s.size();
    int start = 0, end = n - 1;
    while (start < n && s[start] == ' ') start++;
    while (end >= 0 && s[end] == ' ') end--;

    if (start > end) return "";  // if string is all spaces

    s = s.substr(start, end - start + 1);
    n = s.size();

    // Step 2: Reverse the whole string
    reverse(s.begin(), s.end());

    // Step 3: Remove extra spaces and normalize word spacing
    int write = 0;
    for (int read = 0; read < n; read++) {
        if (s[read] != ' ') {
            s[write++] = s[read];
        } else if (write > 0 && s[write - 1] != ' ') {
            s[write++] = ' ';
        }
    }
    s.resize(write);  // remove trailing space if any

    // Step 4: Reverse each individual word
    int wordStart = 0;
    for (int i = 0; i <= write; i++) {
        if (i == write || s[i] == ' ') {
            reverse(s.begin() + wordStart, s.begin() + i);
            wordStart = i + 1;
        }
    }

    return s;
}
```

### Complexity Analysis

**Time Complexity:** `O(n)` — Each character handled a constant number of times

**Space Complexity:** `O(1)` — In-place modifications (ignoring trimmed substring)

---

THE END
