# Number of Provinces (Connected Components)

Author: [Prakash JC](https://prakash079513.github.io/)

## Problem Statement

You are given an **undirected graph** in the form of an adjacency matrix `isConnected`, where:

- `isConnected[i][j] = 1` means there is an edge between city `i` and city `j`.
- `isConnected[i][j] = 0` means no edge.
- Each city is guaranteed to be connected to itself (`isConnected[i][i] = 1`).

A **province** is a group of cities that are directly or indirectly connected.

**Goal:** Find the number of provinces.

---

## Approach using DFS

### Idea

- Each province is essentially a **connected component** in the graph.
- We need to count how many connected components exist.
- Steps:
  1. Initialize a **visited array** of size `n`.
  2. Iterate through each city `i`.
  3. If `i` is not visited, it means we found a new province.
     - Increment the province count.
     - Call DFS to visit all cities reachable from `i`.
  4. Continue until all cities are processed.

### DFS Code (Adjacency Matrix)

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void dfs(int node, vector<vector<int>> &isConnected, vector<int> &visited, int n) {
        visited[node] = 1;
        for (int j = 0; j < n; j++) {
            if (isConnected[node][j] == 1 && !visited[j]) {
                dfs(j, isConnected, visited, n);
            }
        }
    }

    int findCircleNum(vector<vector<int>> &isConnected) {
        int n = isConnected.size();
        vector<int> visited(n, 0);
        int provinces = 0;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                provinces++;
                dfs(i, isConnected, visited, n);
            }
        }
        return provinces;
    }
};
```

### DFS Complexity Analysis

- **Time Complexity:** `O(n²)`
  - Graph is given as adjacency matrix → for each DFS call, we may scan `n` entries.
  - In worst case, every node triggers `O(n)` checks → `O(n²)`.
- **Space Complexity:**
  - `O(n)` for visited array.
  - `O(n)` recursion stack in worst case.

---

## Approach using BFS

### Idea

Same as DFS, but we use a queue to perform level-order traversal.

Steps:

1. Initialize `visited[]`.
2. For each unvisited node `i`, start a BFS:
   - Mark `i` visited, push to queue.
   - While queue is not empty: pop front, explore all neighbors.
   - Mark all reachable nodes as visited.
3. Count how many BFS runs are needed → number of provinces.

### BFS Code (Adjacency Matrix)

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findCircleNum(vector<vector<int>> &isConnected) {
        int n = isConnected.size();
        vector<int> visited(n, 0);
        int provinces = 0;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                provinces++;
                queue<int> q;
                q.push(i);
                visited[i] = 1;

                while (!q.empty()) {
                    int node = q.front();
                    q.pop();

                    for (int j = 0; j < n; j++) {
                        if (isConnected[node][j] == 1 && !visited[j]) {
                            visited[j] = 1;
                            q.push(j);
                        }
                    }
                }
            }
        }
        return provinces;
    }
};
```

---

### BFS Complexity Analysis

- **Time Complexity:** `O(n²)`
  - Adjacency matrix requires scanning all `n` neighbors for each node.
- **Space Complexity:**
  - `O(n)` for visited array.
  - `O(n)` for queue in worst case.

---

THE END
