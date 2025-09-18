# Depth First Search (DFS)

Author: [Prakash JC](https://prakash079513.github.io/)

---

## 1. Introduction

**Depth First Search (DFS)** is a fundamental graph traversal algorithm that explores as far as possible along a branch before backtracking.

- Start from a given source vertex.
- Visit one neighbor, then its neighbor, continuing until no unvisited neighbor remains.
- Backtrack and continue with the next unvisited neighbor.

DFS is often used in problems like detecting cycles, topological sorting, connected components, articulation points, and bridges.

---

## 2. DFS Approach

1. Maintain a **visited array** to track which nodes have been visited.
2. Start DFS from a given node:
   - Mark it as visited.
   - Recursively visit all unvisited neighbors.
3. If the graph is disconnected, repeat DFS for all unvisited vertices.
4. DFS can be implemented in **two ways**:
   - **Recursive (using the system call stack)**
   - **Iterative (using an explicit stack)**

---

## 3. Important Points about DFS

- **DFS goes deep**: It explores one path fully before switching to another.
- **Backtracking**: DFS returns to the previous node when no new unvisited neighbor exists.
- **Visited Array**: Prevents revisiting nodes and infinite recursion.
- **Disconnected Graphs**: Must ensure DFS runs from every unvisited node.
- **Tree vs. Graph DFS**: In trees, no cycles exist, so a visited array is optional; in graphs, it is mandatory.
- **Traversal Order**: DFS order depends heavily on adjacency representation and input ordering.

---

## 4. Implementations

### 4.1 DFS using Adjacency List (Recursive)

### Undirected and 0-based indexing:

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void dfsHelper(int node, vector<int> adj[], vector<int> &visited, vector<int> &dfs) {
        visited[node] = 1;
        dfs.push_back(node);

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfsHelper(neighbor, adj, visited, dfs);
            }
        }
    }

    vector<int> dfsOfGraph(int V, vector<int> adj[]) {
        vector<int> dfs;
        vector<int> visited(V, 0);

        dfsHelper(0, adj, visited, dfs); // start from node 0
        return dfs;
    }
};

int main() {
    int V, E;
    cin >> V >> E;

    vector<int> adj[V];
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // remove for directed graph
    }

    Solution s;
    vector<int> result = s.dfsOfGraph(V, adj);

    for (int x : result) cout << x << " ";
    return 0;
}
```

**Note:**

- Do not forget that the dfs helper is a void fun and does not return anything.
- Here initially it will be call first, then the intial case inside the function.
- Mark it as visited, add it to the result.
- In bfs, it is: remove from the queue and add it to the result.

---

### 4.2 DFS in a Disconnected Graph

The above code explores only one component. For disconnected graphs:

```cpp
vector<int> dfsDisconnected(int V, vector<int> adj[]) {
    vector<int> dfs;
    vector<int> visited(V, 0);

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfsHelper(i, adj, visited, dfs);
        }
    }
    return dfs;
}
```

**Note:**

- No initial case. It is complete ith call.

---

### 4.3 DFS using Iterative Stack

```cpp
void dfsIterative(int V, vector<int> adj[]) {
    vector<int> visited(V, 0);
    vector<int> dfs;
    stack<int> st;

    st.push(0);
    while (!st.empty()) {
        int node = st.top();
        st.pop();

        if (!visited[node]) {
            visited[node] = 1;
            dfs.push_back(node);

            // Push neighbors in reverse order to mimic recursion order
            for (auto it = adj[node].rbegin(); it != adj[node].rend(); it++) {
                if (!visited[*it]) {
                    st.push(*it);
                }
            }
        }
    }

    for (int x : dfs) cout << x << " ";
}
```

### Why reverse and push:

- No problem actually, but jsut to have the same dfs final answer order as the recursion method, we do reverse and push.

**Note:** Flow to read and remember.

- There is initial case like bfs, we need to push it with the first node.
- Remove from the stack.
- NOTE: Unlike bfs, do not add it to the result the instant we remove it out from the stack.
- If it is not visited mark it as visited and then add it to the result.
- Then push all the neighbors in the reverse order if they are not visited.
- Since we wrote the for loop like that, it is an iterator hence, do not forget the asterisk(`*`) symbol.

---

### 4.4 DFS using Adjacency Matrix

```cpp
void dfsMatrixHelper(int node, vector<vector<int>> &adj, vector<int> &visited, vector<int> &dfs, int V) {
    visited[node] = 1;
    dfs.push_back(node);

    for (int v = 0; v < V; v++) {
        if (adj[node][v] && !visited[v]) {
            dfsMatrixHelper(v, adj, visited, dfs, V);
        }
    }
}

vector<int> dfsMatrix(int V, vector<vector<int>> &adj) {
    vector<int> visited(V, 0), dfs;
    dfsMatrixHelper(0, adj, visited, dfs, V);
    return dfs;
}
```

---

## 5. Complexity Analysis

### Using Adjacency List

- **Time Complexity:** `O(V + E)`
  - Each vertex visited once.
  - Each edge checked once (directed) or twice (undirected → `2E`).
- **Space Complexity:**
  - `O(V)` for visited array.
  - `O(V)` for recursion stack (worst case depth).
  - `O(V + E)` for adjacency list.

### Using Adjacency Matrix

- **Time Complexity:** `O(V²)` – check all neighbors for each vertex.
- **Space Complexity:** `O(V²)` for matrix + `O(V)` for visited.

---

THE END
