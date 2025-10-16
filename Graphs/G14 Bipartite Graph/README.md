## Check if a Graph is Bipartite

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

You are given an undirected graph represented as an adjacency list `adj` with `V` vertices (0-based indexing).

Determine whether the graph is **bipartite**.

A graph is **bipartite** if we can color all vertices using **two colors** such that **no two adjacent vertices share the same color**.

## Recommended Approach: **BFS**

The concept of bipartiteness is directly tied to **graph coloring**.

1. We attempt to color the graph using **two colors (say, 0 and 1)**.
2. If we can color all nodes such that no two adjacent nodes have the same color, then the graph is bipartite.
3. The graph can be **disconnected**, so we must check each component individually.
4. For each unvisited node:
   - Assign it a starting color (say 0).
   - Perform BFS:
     - For every adjacent node:
       - If it’s uncolored, assign the opposite color.
       - If it’s already colored with the same color as the current node, the graph is **not bipartite**.
5. If all components are colored without conflicts, the graph is bipartite.

### Code (BFS)

```cpp
bool bfsCheck(int start, vector<vector<int>>& adj, vector<int>& color) {
    queue<int> q;
    q.push(start);
    color[start] = 0;  // Start coloring with 0

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (auto neighbor : adj[node]) {
            // If neighbor not colored, color with opposite color
            if (color[neighbor] == -1) {
                color[neighbor] = 1 - color[node];
                q.push(neighbor);
            }
            // If neighbor has same color, not bipartite
            else if (color[neighbor] == color[node]) {
                return false;
            }
        }
    }
    return true;
}

bool isBipartite(vector<vector<int>>& adj) {
    int V = adj.size();
    vector<int> color(V, -1);  // -1 means uncolored

    for (int i = 0; i < V; i++) {
        if (color[i] == -1) {
            if (!bfsCheck(i, adj, color))
                return false;
        }
    }
    return true;
}
```

### Complexity Analysis

**Time Complexity:** `O(V + E)` – Each vertex and edge is visited once during BFS.

**Space Complexity:** `O(V)` – For the color array and BFS queue.

## **DFS** Approach

1. We again try to color the graph using two colors — `0` and `1`.
2. For each unvisited node:
   - Assign a starting color (`0`).
   - Perform **DFS**:
     - For every adjacent node:
       - If it’s uncolored, recursively color it with the opposite color.
       - If it’s already colored with the same color as the current node, the graph is **not bipartite**.
3. If all components are colored successfully, the graph is bipartite.

### Code (DFS)

```cpp
bool dfsCheck(int node, int colorVal, vector<vector<int>>& adj, vector<int>& color) {
    color[node] = colorVal;

    for (auto neighbor : adj[node]) {
        if (color[neighbor] == -1) {
            if (!dfsCheck(neighbor, 1 - colorVal, adj, color))
                return false;
        }
        else if (color[neighbor] == color[node]) {
            return false;
        }
    }
    return true;
}

bool isBipartite(vector<vector<int>>& adj) {
    int V = adj.size();
    vector<int> color(V, -1);

    for (int i = 0; i < V; i++) {
        if (color[i] == -1) {
            if (!dfsCheck(i, 0, adj, color))
                return false;
        }
    }
    return true;
}
```

### Complexity Analysis

**Time Complexity:** `O(V + E)` – Each vertex and edge is visited once in DFS.

**Space Complexity:** `O(V)` – For the color array and recursion stack.

---

THE END
