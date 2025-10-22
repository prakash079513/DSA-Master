## Alien Dictionary

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

Given a sorted dictionary of an alien language containing `N` words and `K` distinct characters (from some unknown alphabet), find the order of characters in that alien language.

If multiple valid orders exist, return any one of them.

---

### Intuition

In an alien dictionary, the order of words follows the lexicographical rules of the **alien alphabet**.

We can compare adjacent words in the given sorted list — the first position where they differ tells us the **relative order** between two characters (like `'b'` comes before `'a'`).

Once we gather all such relations, we can model them as a **directed graph** and use **Topological Sorting** to derive a valid order of characters.

This is a direct application of **Kahn’s Algorithm (BFS)** or **DFS-based Topological Sort** — since the problem defines dependencies between characters.

---

### Approach (Using Kahn’s Algorithm – BFS Topological Sort)

1. **Build a Directed Graph:**
   - Initialize an adjacency list of size `K` (for each character from `0` to `K-1`).
   - For each pair of consecutive words in the dictionary:
     - Compare characters until you find the first differing character.
     - Suppose they differ at `c1` and `c2`, then there is a directed edge `c1 → c2`.
     - This means `c1` must appear before `c2` in the alien language.
2. **Compute Indegree:**
   - For each vertex (character), count the number of incoming edges.
3. **Apply Kahn’s Algorithm (BFS Topo Sort):**
   - Push all nodes with `indegree = 0` into a queue (these have no dependencies).
   - Repeatedly pop from the queue, append to the order, and decrease the indegree of neighbors.
   - If any neighbor’s indegree becomes 0, push it into the queue.
4. **Convert Back to Characters:**
   - The final topological order (of indices) can be mapped back to characters (`'a' + i`).
5. **Return the Result:**
   - The final sequence gives a valid character ordering for the alien language.

---

### Code

```cpp
string findOrder(string dict[], int N, int K) {
    vector<vector<int>> adj(K);

    // Step 1: Build the graph
    for (int i = 0; i < N - 1; i++) {
        string s1 = dict[i];
        string s2 = dict[i + 1];
        int len = min(s1.size(), s2.size());

        for (int j = 0; j < len; j++) {
            if (s1[j] != s2[j]) {
                adj[s1[j] - 'a'].push_back(s2[j] - 'a');
                break;
            }
        }
    }

    // Step 2: Compute indegree
    vector<int> indegree(K, 0);
    for (int i = 0; i < K; i++) {
        for (auto it : adj[i]) indegree[it]++;
    }

    // Step 3: Kahn's Algorithm
    queue<int> q;
    for (int i = 0; i < K; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    string order = "";
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        order += (char)(node + 'a');

        for (auto neigh : adj[node]) {
            indegree[neigh]--;
            if (indegree[neigh] == 0) q.push(neigh);
        }
    }

    return order;
}
```

---

### Complexity Analysis

**Time Complexity:** `O(N * L + K + E)`

- `O(N * L)` to compare adjacent words (where `L` is average word length).
- `O(K + E)` for topological sorting.

**Space Complexity:** `O(K + E)`

- For storing the adjacency list, indegree array, and queue.

---

THE END
