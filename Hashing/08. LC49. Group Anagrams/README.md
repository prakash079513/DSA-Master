### **49. Group Anagrams**

Author: Prakash JC

### Problem Statement

Given an array of strings `strs`, group the anagrams together. You can return the answer in any order.

An anagram is a word formed by rearranging the letters of another word using all the original letters exactly once.

---

### Key Takeaway

- all anagrams produce the same canonical representation (sorted string or frequency count).

---

### Brute Force Approach

#### Approach

- Create a `visited` array initialized to `false`.
- Traverse every string.
- For each unvisited string:
  - Mark it as visited.
  - Compare it with every remaining unvisited string.
  - Sort both strings and compare them.
  - If they are equal, they belong to the same group.

- Add the group to the answer.

**Time Complexity:** `O(n² · k log k)`

**Space Complexity:** `O(n)`

where:

- `n` = number of strings
- `k` = average length of a string

---

### Better Approach – Sort Every String

#### Key Observation

- Two strings are anagrams if their sorted forms are identical.
- The sorted string can be used as a unique key.

#### Approach

- Create a hashmap:
  - Key → sorted string
  - Value → list of original strings

- Traverse every string.
- Make a copy of the string.
- Sort the copied string.
- Insert the original string into the hashmap using the sorted string as the key.
- Traverse the hashmap and collect all groups.

### Code

```cpp id="vpmg7v"
vector<vector<string>> groupAnagrams(vector<string>& strs) {

    unordered_map<string, vector<string>> mp;

    for (string str : strs) {
        string temp = str;
        sort(temp.begin(), temp.end());

        mp[temp].push_back(str);
    }

    vector<vector<string>> ans;

    for (auto it : mp)
        ans.push_back(it.second);

    return ans;
}
```

**Time Complexity:** `O(n · k log k)`

**Space Complexity:** `O(n · k)`

---

### Optimal Approach – Character Frequency as Key

#### Key Observation

- Sorting every string costs `O(k log k)`.
- Instead, count the frequency of each character.
- Every anagram has the same frequency array.
- Convert the frequency array into a unique string key.

#### Approach

- Create a hashmap:
  - Key → frequency string
  - Value → list of original strings

- Traverse every string.
- Create a frequency array of size 26.
- Count occurrences of every character.
- Convert the frequency array into a unique key.
- Insert the original string into the hashmap.
- Collect all groups from the hashmap.

### Code

```cpp id="1ddhym"
vector<vector<string>> groupAnagrams(vector<string>& strs) {

    unordered_map<string, vector<string>> mp;

    for (string str : strs) {

        vector<int> freq(26, 0);

        for (char c : str)
            freq[c - 'a']++;

        string key;

        for (int i = 0; i < 26; i++) {
            key += "#";
            key += to_string(freq[i]);
        }

        mp[key].push_back(str);
    }

    vector<vector<string>> ans;

    for (auto it : mp)
        ans.push_back(it.second);

    return ans;
}
```

**Time Complexity:** `O(n · k)`

**Space Complexity:** `O(n · k)`

---

THE END
