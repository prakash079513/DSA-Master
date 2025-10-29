## Word Ladder I

Author: [Prakash JC](https://prakash079513.github.io/)

## Problem Statement

Given two distinct words `startWord` and `targetWord`, and a list `wordList` of unique lowercase words of equal length, find the **length of the shortest transformation sequence** to convert `startWord` → `targetWord`.

**Rules**

A transformation changes exactly one letter

Every transformed word must exist in `wordList`

Return `0` if transformation is not possible

**Example**

startWord = der

targetWord = dfs

wordList = {des, der, dfr, dgt, dfs}

Answer = 3

der → dfr → dfs

---

## Intuition

We need the **minimum number of transformations**.

Each valid transformed word can be seen as a **node** in a graph, and there is an **edge** if two words differ by exactly one character.

We perform **Breadth First Search BFS** from `startWord` to find the shortest path to `targetWord`.

---

## Approach

1. Convert `wordList` into a set for fast lookup
2. Use a queue for BFS storing `{word, level}`
3. For each word taken from queue

   Change each position with letters from `a` to `z` and form a new word

   If it exists in the set, push it into queue and erase from set

4. When `targetWord` is reached, return the current level
5. If BFS ends without reaching targetWord, return `0`

---

## Code

```cpp
int ladderLength(string startWord, string targetWord, vector<string>& wordList) {
    unordered_set<string> st(wordList.begin(), wordList.end());
    if(!st.count(targetWord)) return 0;

    queue<pair<string,int>> q;
    q.push({startWord, 1});
    st.erase(startWord);

    while(!q.empty()) {
        auto [word, level] = q.front();
        q.pop();

        if(word == targetWord) return level;

        for(int i = 0; i < word.size(); i++) {
            char original = word[i];

            for(char c = 'a'; c <= 'z'; c++) {
                word[i] = c;
                if(st.count(word)) {
                    q.push({word, level + 1});
                    st.erase(word);
                }
            }
            word[i] = original;
        }
    }
    return 0;
}
```

---

## Complexity Analysis

Time Complexity: `O(N * M * 26)`

N = size of wordList, M = length of each word

We generate 26\*M neighbors per word

Space Complexity: `O(N)`For BFS queue and unordered_set storage

---

THE END
