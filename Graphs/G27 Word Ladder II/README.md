# Word Ladder II

Author: [Prakash JC](https://prakash079513.github.io/)

## Problem Statement

Given two distinct words `startWord` and `targetWord`, and a list of unique lowercase words `wordList`, return **all shortest transformation sequences** from `startWord` → `targetWord`.

Rules

Only 1 letter can change per transformation

Each intermediate word must exist in `wordList`

If no path exists, return an empty list

Example

startWord = hit

targetWord = cog

wordList = {hot, dot, dog, lot, log, cog}

Output =

hit → hot → dot → dog → cog

hit → hot → lot → log → cog

---

### Intuition

Unlike Word Ladder I, we must return **all shortest paths**.

Key idea: **Graph BFS + Path Recovery**.

Steps

First: BFS to find the shortest distance to each reachable word

Second: Backtrack from targetWord using stored parent relations

This avoids exploring longer or invalid paths.

---

### Approach

1. Insert all wordList into a set
2. Use BFS from startWord
   - Maintain a **map of parents** for each reachable word
   - Maintain `level` words visited in one BFS layer
   - When a word is visited first time, record its parent
3. Stop BFS when `targetWord` level is fully processed
4. Use **DFS backtracking** on the parent map to recover all shortest paths

---

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<string>> ans;

    void dfs(string word, string &start,
             unordered_map<string, vector<string>> &parent,
             vector<string> &path) {
        if (word == start) {
            reverse(path.begin(), path.end());
            ans.push_back(path);
            reverse(path.begin(), path.end());
            return;
        }
        for (auto &p : parent[word]) {
            path.push_back(p);
            dfs(p, start, parent, path);
            path.pop_back();
        }
    }

    vector<vector<string>> findLadders(string startWord, string targetWord, vector<string>& wordList) {
        unordered_set<string> st(wordList.begin(), wordList.end());
        vector<vector<string>> emptyRes;
        if (!st.count(targetWord)) return emptyRes;

        unordered_map<string, vector<string>> parent;
        queue<string> q;
        q.push(startWord);

        unordered_set<string> visited;
        visited.insert(startWord);

        bool found = false;

        while (!q.empty()) {
            int size = q.size();
            unordered_set<string> thisLevel;

            while (size--) {
                string word = q.front();
                q.pop();

                string original = word;

                for (int i = 0; i < word.size(); i++) {
                    char old = word[i];
                    for (char c = 'a'; c <= 'z'; c++) {
                        word[i] = c;

                        if (st.count(word)) {
                            if (!visited.count(word)) {
                                q.push(word);
                                thisLevel.insert(word);
                                parent[word].push_back(original);
                            }
                            else if (thisLevel.count(word)) {
                                parent[word].push_back(original);
                            }
                            if (word == targetWord) found = true;
                        }
                    }
                    word[i] = old;
                }
            }

            for (auto &w : thisLevel) visited.insert(w);
            if (found) break;
        }

        if (!found) return emptyRes;

        vector<string> path;
        path.push_back(targetWord);
        dfs(targetWord, startWord, parent, path);

        return ans;
    }
};

int main() {
    vector<string> wordList = {"hot","dot","dog","lot","log","cog"};
    string startWord = "hit", targetWord = "cog";
    Solution s1;
    auto res = s1.findLadders(startWord, targetWord, wordList);
    for (auto &v : res) {
        for (auto &s : v) cout << s << " ";
        cout << "\n";
    }
    return 0;
}

```

---

### Complexity Analysis

Time Complexity: `O(N * M * 26)` for BFS + path reconstruction

N = size of wordList, M = word length

Multiple parents stored increases branching during backtracking

Space Complexity: `O(N)`

Parent map, BFS queue, recursion stack

---

## Approach 2: Might be TLE/MLE on big lists

- **Insert all words into set `st`** for O(1) lookup.
- Start BFS with path containing: `{beginWord}`.
- `level` counts BFS levels (path length).
- When moving to a _new_ level:
  - Remove all used words from the set → prevents revisiting earlier levels.
- For each candidate path:
  - Try replacing each character in the last word with `'a'` → `'z'`
  - If new word exists in the set: → push into path and enqueue
- When `endWord` is reached:
  - If `ans` is empty → push first sequence
  - Else push only if the path length matches the first (shortest)
- When BFS ends → return all stored shortest sequences

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<string>> findSequences(string beginWord, string endWord, vector<string> &wordList) {
        unordered_set<string> st(wordList.begin(), wordList.end());
        queue<vector<string>> q;
        q.push({beginWord});
        vector<string> usedOnLevel;
        usedOnLevel.push_back(beginWord);
        int level = 0;
        vector<vector<string>> ans;
        while (!q.empty()) {
            vector<string> vec = q.front();
            q.pop();
            if (vec.size() > level) {
                level++;
                for (auto it : usedOnLevel) {
                    st.erase(it);
                }
            }
            string word = vec.back();
            if (word == endWord) {
                if (ans.size() == 0) {
                    ans.push_back(vec);
                } else if (ans[0].size() == vec.size()) {
                    ans.push_back(vec);
                }
            }
            for (int i = 0; i < word.size(); i++) {
                char original = word[i];
                for (char c = 'a'; c <= 'z'; c++) {
                    word[i] = c;
                    if (st.count(word) > 0) {
                        vec.push_back(word);
                        q.push(vec);
                        usedOnLevel.push_back(word);
                        vec.pop_back();
                    }
                }
                word[i] = original;
            }
        }
        return ans;
    }
};

bool comp(vector<string> a, vector<string> b) {
    string x = "", y = "";
    for (string i : a) x += i;
    for (string i : b) y += i;
    return x < y;
}

int main() {
    vector<string> wordList = {"des", "der", "dfr", "dgt", "dfs"};
    string startWord = "der", targetWord = "dfs";
    Solution obj;
    vector<vector<string>> ans = obj.findSequences(startWord, targetWord, wordList);
    if (ans.size() == 0) cout << -1 << endl;
    else {
        sort(ans.begin(), ans.end(), comp);
        for (int i = 0; i < ans.size(); i++) {
            for (int j = 0; j < ans[i].size(); j++) {
                cout << ans[i][j] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
```

### Complexity Analysis

**Time Complexity:** `O(N * L * 26)` — BFS explores every valid word by trying all 26 character substitutions.

**Space Complexity:** `O(N * L)` — storing multiple transformation paths in the BFS queue and used word tracking.

---

THE END
