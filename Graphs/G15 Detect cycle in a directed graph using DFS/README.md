## **Detect cycle in a directed graph using DFS**

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

Given a directed graph with `V` vertices and `E` edges represented as an adjacency list, determine whether it contains a **cycle**.

A cycle exists in a directed graph if there is a path from a node back to itself through a sequence of directed edges.

## Approach 1: **Using Two Visited Arrays**

We use two arrays:

- `visited[]` → marks whether a node has been visited in **any** DFS traversal.
- `pathVisited[]` → marks whether a node is **currently** in the recursion stack (i.e., the current DFS path).

If we ever encounter a node that is **already visited in the current path**, we’ve found a cycle.

---

### Steps

1. For every unvisited node, start a DFS.
2. Mark `visited[node] = 1` and `pathVisited[node] = 1`.
3. For each neighbor:
   - If it’s **not visited**, call DFS on it.
   - If it’s **already visited and pathVisited[neighbor] = 1**, a cycle exists.
4. After exploring all neighbors, mark `pathVisited[node] = 0` before returning.
5. If no back edge is found, the graph is acyclic.

### Code (Two visited arrays)

```cpp
bool dfs(int node, vector<vector<int>>& adj, vector<int>& visited, vector<int>& pathVisited) {
    visited[node] = 1;
    pathVisited[node] = 1;

    for (auto neighbor : adj[node]) {
        if (!visited[neighbor]) {
            if (dfs(neighbor, adj, visited, pathVisited))
                return true;
        }
        else if (pathVisited[neighbor]) {
            return true; // back edge found
        }
    }

    pathVisited[node] = 0; // backtrack
    return false;
}

bool isCyclic(int V, vector<vector<int>>& adj) {
    vector<int> visited(V, 0), pathVisited(V, 0);

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (dfs(i, adj, visited, pathVisited))
                return true;
        }
    }
    return false;
}
```

### Complexity Analysis

**Time Complexity:** `O(V + E)` – Every vertex and edge is visited once.

**Space Complexity:** `O(V)` – For recursion stack and visited arrays.

## Approach 2: **Using One Visited Array with State Marking**

### Idea

Instead of maintaining two separate arrays, we use a **single array** `state[]` with three states:

- `0` → unvisited
- `1` → currently in recursion stack (in path)
- `2` → completely processed

If we ever reach a node with `state = 1` (currently in stack), we found a back edge ⇒ cycle detected.

---

### Steps

1. For each unvisited node (`state = 0`), call DFS.
2. Mark `state[node] = 1` (currently visiting).
3. For each neighbor:
   - If `state[neighbor] = 1`, a cycle exists.
   - If `state[neighbor] = 0`, recurse.
4. After visiting all neighbors, mark `state[node] = 2` (fully processed).

### Code (Single array method)

```cpp
bool dfs(int node, vector<vector<int>>& adj, vector<int>& state) {
    state[node] = 1; // visiting

    for (auto neighbor : adj[node]) {
        if (state[neighbor] == 0) {
            if (dfs(neighbor, adj, state))
                return true;
        }
        else if (state[neighbor] == 1) {
            return true; // back edge found
        }
    }

    state[node] = 2; // processed
    return false;
}

bool isCyclic(int V, vector<vector<int>>& adj) {
    vector<int> state(V, 0); // 0 - unvisited, 1 - visiting, 2 - processed

    for (int i = 0; i < V; i++) {
        if (state[i] == 0) {
            if (dfs(i, adj, state))
                return true;
        }
    }
    return false;
}
```

### Complexity Analysis

**Time Complexity:** `O(V + E)` – Each node and edge is processed once.

**Space Complexity:** `O(V)` – For recursion and state tracking.

---

THE END
