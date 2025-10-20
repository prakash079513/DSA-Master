## Eventual Safe States (DFS Approach)

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

You are given a directed graph with `V` vertices (numbered `0` to `V-1`) represented as an adjacency list `adj`.

A node is called **terminal** if it has **no outgoing edges**.

A node is called **safe** if every possible path starting from it eventually leads to a terminal node — in other words, **no path from it leads to a cycle**.

You must return all the **safe nodes** in sorted order.

---

### Recommended Approach: **Depth-First Search (DFS)**

### Intuition

This problem is conceptually related to **cycle detection in a directed graph**, but with a twist.

- If a node leads to a **cycle**, it is **unsafe**.
- If all paths from a node eventually lead to **terminal nodes** (nodes with no outgoing edges), it is **safe**.

We use **DFS** to detect cycles and mark nodes as safe or unsafe based on traversal results.

---

### Approach

1. **Use three arrays:**
   - `visited[]` → tracks if a node has been visited.
   - `pathVisited[]` → tracks nodes currently in the recursion stack.
   - `check[]` → marks whether a node is **safe (1)** or **unsafe (0)**.
2. For every unvisited node, perform a DFS:
   - Mark `visited[node] = 1` and `pathVisited[node] = 1`.
   - Explore all neighbors:
     - If a neighbor is **unvisited**, recursively perform DFS.
       - If that DFS call finds a cycle (`true`), mark current node as unsafe.
     - If a neighbor is **already in the recursion stack (`pathVisited[neighbor] = 1`)**, that means we’ve found a cycle — mark current node as unsafe.
   - After exploring all neighbors:
     - Mark `pathVisited[node] = 0` (backtrack).
     - If no cycle was found from this node, mark it as **safe** (`check[node] = 1`).
3. Finally, all nodes with `check[node] = 1` are **safe nodes**.

### Code (DFS)

```cpp
bool dfs(int node, vector<vector<int>>& adj, vector<int>& visited,
            vector<int>& pathVisited, vector<int>& check) {
    visited[node] = 1;
    pathVisited[node] = 1;

    for (auto neighbor : adj[node]) {
        // If neighbor not visited, do DFS
        if (!visited[neighbor]) {
            if (dfs(neighbor, adj, visited, pathVisited, check)) {
                check[node] = 0;
                return true;  // cycle detected
            }
        }
        // If neighbor is in the current path → cycle found
        else if (pathVisited[neighbor]) {
            check[node] = 0;
            return true;
        }
    }

    // No cycle found, mark node as safe
    check[node] = 1;
    pathVisited[node] = 0;  // backtrack
    return false;
}

vector<int> eventualSafeNodes(vector<vector<int>>& adj) {
    int V = adj.size();
    vector<int> visited(V, 0), pathVisited(V, 0), check(V, 0);

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfs(i, adj, visited, pathVisited, check);
        }
    }

    vector<int> safeNodes;
    for (int i = 0; i < V; i++) {
        if (check[i] == 1) safeNodes.push_back(i);
    }
    return safeNodes;
}
```

### Complexity Analysis

**Time Complexity:** `O(V + E)`

- Each node and edge is visited once during the DFS traversal.

**Space Complexity:** `O(V)`

- For `visited`, `pathVisited`, `check` arrays and recursion stack.

---

## **Expected Approach (in contests and interviews)**

### **Idea**

Use a **single `vis` array** that stores the _state_ of each node using three distinct values:

- `0` → Node not visited yet
- `1` → Node currently in the recursion stack (path)
- `2` → Node already processed and found to be safe

**Reason it’s preferred:**

- It’s **cleaner**, **space-efficient**, and **intuitively represents** all required information.
- Interviewers look for compact, efficient code that avoids redundant arrays (like `pathVis` or `check`).
- It’s the **same conceptual foundation** as cycle detection in directed graphs but reused to classify safe nodes.

### **Approach**

1. Perform DFS from each unvisited node.
2. When a node enters DFS, mark it as `1` (currently visiting).
3. Explore all its neighbors:
   - If any neighbor is `1`, a cycle is found → mark node as unsafe.
   - If any neighbor leads to a cycle, current node is unsafe.
4. If no cycle is found, mark node as `2` (safe).
5. Finally, collect all nodes with `vis[i] == 2` — these are the **eventual safe nodes**.

### **Code (Single `vis` Array Approach)**

```cpp
bool dfs(int node, vector<int> adj[], vector<int>& vis) {
    vis[node] = 1; // node in current path
    for (auto it : adj[node]) {
        if (vis[it] == 0) {
            if (dfs(it, adj, vis)) return true; // cycle found
        }
        else if (vis[it] == 1) return true; // back edge → cycle
    }
    vis[node] = 2; // safe node
    return false;  // no cycle found
}

vector<int> eventualSafeNodes(int V, vector<int> adj[]) {
    vector<int> vis(V, 0);
    for (int i = 0; i < V; i++) {
        if (vis[i] == 0) dfs(i, adj, vis);
    }

    vector<int> safe;
    for (int i = 0; i < V; i++) {
        if (vis[i] == 2) safe.push_back(i);
    }
    return safe;
}
```

### **Complexity Analysis**

**Time Complexity:** `O(V + E)` – Every node and edge is visited once in the DFS traversal.

**Space Complexity:** `O(V)` – The `vis` array and recursion stack use linear space.

---

THE END
