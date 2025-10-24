## Shortest Path in Undirected Graph with Unit Distance

Author: [Prakash JC](https://prakash079513.github.io/)

## Problem Statement

Given an **undirected graph** having **unit weights (each edge has weight = 1)**, find the **shortest path** from a given **source node (0)** to **all other nodes** in the graph.

If a vertex is **unreachable** from the source node, return **-1** for that vertex.

---

### Intuition

In an **unweighted graph**, the shortest path from a source node can be efficiently found using **Breadth-First Search (BFS)**.

BFS explores all nodes at the current distance level before moving to the next — hence, the first time we reach a node, it is guaranteed to be via the shortest path.

---

### Approach (Using BFS)

1. **Build the Adjacency List:**
   - Convert the list of edges into an adjacency list for efficient traversal.
   - Since the graph is undirected, add both `u → v` and `v → u`.
2. **Initialize Distance Array:**
   - Create a distance array `dist[]` of size `n`, initialized with a large value (say `1e9`).
   - Set `dist[0] = 0` (distance to the source node itself).
3. **Run BFS from the Source Node:**
   - Use a queue to perform BFS traversal.
   - Push the source node (0) into the queue.
   - For every node `u` popped from the queue, check all its neighbors `v`.
   - If `dist[v] > dist[u] + 1`, update `dist[v] = dist[u] + 1` and push `v` into the queue.
4. **Handle Unreachable Nodes:**
   - After BFS completes, replace all nodes still having `dist[i] == 1e9` with `-1`.
5. **Return Result**

---

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> shortestPath(int n, vector<vector<int>>& edges) {
        // Step 1: Build adjacency list
        vector<vector<int>> adj(n);
        for (auto& e : edges) { // Write loop like this, it is good.
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        // Step 2: Initialize distance array
        const int INF = 1e9;
        vector<int> dist(n, INF);
        dist[0] = 0; // Do not forget to initialize the source

        // Step 3: BFS traversal
        queue<int> q;
        q.push(0);

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int neighbor : adj[node]) { // Update and push
                if (dist[neighbor] > dist[node] + 1) {
                    dist[neighbor] = dist[node] + 1;
                    q.push(neighbor);
                }
            }
        }

        // Step 4: Replace unreachable nodes with -1
        for (int& d : dist) {
            if (d == INF) d = -1;
        }

        return dist;
    }
```

### Complexity Analysis

**Time Complexity:** `O(V + E)`

- Each node and edge is processed once during BFS traversal.

**Space Complexity:** `O(V + E)`

- For storing the adjacency list, queue, and distance array.

---

THE END
