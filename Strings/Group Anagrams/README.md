# Group Anagrams

Author: [Prakash JC](https://prakash079513.github.io/)

## Problem Statement

You are given an array of strings **strs**.

Group all anagrams together and return the groups in any order.

Constraints:

- Only lowercase English letters
- `1 ≤ strs.length ≤ 10⁴`
- `0 ≤ strs[i].length ≤ 100`

---

## Brute Force Approach

### Approach

- For each string, sort the characters
- Compare sorted results with other strings to find anagrams
- Use visited marking to avoid regrouping

### Code (Brute Force)

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        int n = strs.size();
        vector<bool> vis(n, false);
        vector<vector<string>> ans;

        for (int i = 0; i < n; i++) {
            if (vis[i]) continue;
            vis[i] = true;
            vector<string> group = {strs[i]};

            string s1 = strs[i];
            sort(s1.begin(), s1.end());

            for (int j = i + 1; j < n; j++) {
                if (!vis[j]) {
                    string s2 = strs[j];
                    sort(s2.begin(), s2.end());
                    if (s1 == s2) {
                        vis[j] = true;
                        group.push_back(strs[j]);
                    }
                }
            }
            ans.push_back(group);
        }
        return ans;
    }
};

int main() {
    vector<string> strs = {"eat","tea","tan","ate","nat","bat"};
    Solution sol;
    vector<vector<string>> res = sol.groupAnagrams(strs);
    return 0;
}
```

### Complexity Analysis

**Time Complexity:** `O(n² * k log k)` — For each string, sort and compare with others.

**Space Complexity:** `O(n)` — Visited array and output storage.

---

## Expected Optimal Solution (Hashing with Sorted Key)

### Approach

- For each string, sort characters → this sorted string is the key
- Store all original strings with same key in a HashMap
- Return values of HashMap

### Code (Optimal)

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> mp;

        for (string s : strs) {
            string key = s;
            sort(key.begin(), key.end());
            mp[key].push_back(s);
        }

        vector<vector<string>> ans;
        for (auto &entry : mp) {
            ans.push_back(entry.second);
        }
        return ans;
    }
};

int main() {
    vector<string> strs = {"eat","tea","tan","ate","nat","bat"};
    Solution sol;
    vector<vector<string>> res = sol.groupAnagrams(strs);
    return 0;
}
```

### Complexity Analysis

**Time Complexity:** `O(n * k log k)` — Sorting each string of length k once.

**Space Complexity:** `O(n * k)` — HashMap stores all strings grouped.

---

THE END
