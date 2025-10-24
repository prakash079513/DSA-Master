# Shortest Path in DAG using Topo Sort

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

Given a **Directed Acyclic Graph (DAG)** with `N` vertices and `M` edges, where each edge `(u, v, w)` represents an edge from `u` to `v` with weight `w`, find the **shortest path** from a given source node (usually `0`) to all other nodes.

If a node is not reachable from the source, its distance should be reported as infinity (or a large number like `1e9`).

## Intuition

In a DAG, there are **no cycles**, which means we can process vertices in **topological order** to ensure that when we relax edges of a vertex, the shortest distance to all its predecessors is already finalized.

This gives us a very efficient and elegant solution that’s faster than Dijkstra for DAGs (`O(V + E)` instead of `O(E log V)`).

# **Approach 1: DFS + Topological Sort**

### Steps:

1. **Build the adjacency list** — for each edge `(u, v, w)`, store `(v, w)` in `adj[u]`.
2. **Perform Topological Sort using DFS:**
   - Recursively visit nodes and push them into a stack after visiting all their neighbors.
   - The stack will then store nodes in reverse topological order.
3. **Initialize the distance array** with `dist[source] = 0` and all others as `1e9`.
4. **Relax edges in topological order:**
   - Pop nodes from the stack one by one.
   - For each neighbor `(v, w)` of `node`, update `dist[v] = min(dist[v], dist[node] + w)`.

## Code (DFS Topo Sort Approach)

```cpp
void topoDFS(int node, vector<pair<int,int>> adj[], vector<int> &vis, stack<int> &st) {
    vis[node] = 1;
    for (auto it : adj[node]) {
        int v = it.first;
        if (!vis[v]) topoDFS(v, adj, vis, st);
    }
    st.push(node);
}

vector<int> shortestPath(int N, int M, vector<vector<int>> &edges) {
    vector<pair<int,int>> adj[N]; // Take vector of pairs.
    for (int i = 0; i < M; i++) { // Note: Till M only. Do not forget.
        int u = edges[i][0], v = edges[i][1], w = edges[i][2];
        adj[u].push_back({v, w});
    }

    vector<int> vis(N, 0);
    stack<int> st;
    for (int i = 0; i < N; i++) {
        if (!vis[i]) topoDFS(i, adj, vis, st);
    }

    vector<int> dist(N, 1e9);
    dist[0] = 0; // Note: Initialize the source. Do not forget.

    while (!st.empty()) {
        int node = st.top();
        st.pop();

        if (dist[node] != 1e9) {
            for (auto it : adj[node]) {
                int v = it.first, w = it.second;
                if (dist[node] + w < dist[v]) {
                    dist[v] = dist[node] + w;
                }
            }
        }
    }
    return dist;
}
```

## Complexity Analysis

**Time Complexity:** `O(V + E)` – Each vertex and edge is processed once.

**Space Complexity:** `O(V + E)` – For adjacency list, stack, and distance array.

# **Approach 2: BFS + Topological Sort (Kahn’s Algorithm)**

### Steps:

1. **Build adjacency list and indegree array.**
2. **Perform Topological Sort using Kahn’s Algorithm:**
   - Push all nodes with `indegree = 0` into a queue.
   - Process nodes level-by-level and store them in topological order.
3. **Initialize distance array** with `dist[source] = 0`.
4. **Relax edges in topological order:**
   - For each node in topo order, relax all its outgoing edges `(v, w)` as `dist[v] = min(dist[v], dist[u] + w)`.

## Code (BFS Topo Sort – Kahn’s Algorithm)

```cpp
vector<int> shortestPath(int N, int M, vector<vector<int>> &edges) {
    vector<pair<int,int>> adj[N];
    vector<int> indegree(N, 0);

    for (int i = 0; i < M; i++) {
        int u = edges[i][0], v = edges[i][1], w = edges[i][2];
        adj[u].push_back({v, w});
        indegree[v]++;
    }

    queue<int> q;
    for (int i = 0; i < N; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    vector<int> topo;
    while (!q.empty()) {
        int node = q.front(); q.pop();
        topo.push_back(node);
        for (auto it : adj[node]) {
            indegree[it.first]--;
            if (indegree[it.first] == 0) q.push(it.first);
        }
    }

    vector<int> dist(N, 1e9);
    dist[0] = 0;

    for (auto node : topo) {
        if (dist[node] != 1e9) {
            for (auto it : adj[node]) {
                int v = it.first, w = it.second;
                if (dist[node] + w < dist[v]) {
                    dist[v] = dist[node] + w;
                }
            }
        }
    }

    return dist;
}
```

## Complexity Analysis

**Time Complexity:** `O(V + E)` – Topological sorting and single pass over all edges.

**Space Complexity:** `O(V + E)` – For adjacency list, indegree array, and distance array.

---

THE END
