# Print Shortest Path

**Author:** [Prakash JC](https://prakash079513.github.io/)

## Problem Statement

Given a weighted undirected graph with `V` vertices and `E` edges, and two nodes `1` (source) and `V` (destination), find the **shortest path** from node `1` to node `V`.

If there is no path, return `{-1}`.

If a path exists, return the **actual sequence of nodes** along the shortest path.

---

### Intuition

In a normal Dijkstra’s algorithm, we only track the shortest distance from the source to each node.

To reconstruct the actual path, we must additionally **store the parent of each node** — i.e., the node from which the current node got its shortest distance update.

At the end, we backtrack from the destination node using this `parent` array to build the path.

---

### Approach

1. Use **Dijkstra’s algorithm** with a **min-heap (priority queue)**.
2. Maintain:
   - `dist[i]` → shortest distance from source to `i`
   - `parent[i]` → the previous node on the shortest path to `i`
3. Initialize:
   - `dist[source] = 0`, `parent[source] = source`
4. For each neighbor `(v, wt)` of `u`, if `dist[u] + wt < dist[v]`:
   - Update `dist[v]`
   - Set `parent[v] = u`
   - Push `(dist[v], v)` into PQ
5. After processing, reconstruct path:
   - Start from destination `V`
   - Move backward using `parent[V]` until reaching `source`
   - Reverse the path
6. If destination is unreachable (`dist[V] == INF`), return `{-1}`.

---

### Code

```cpp
vector<int> shortestPath(int V, int E, vector<vector<int>> &edges) {
    vector<pair<int,int>> adj[V+1];
    for (auto &e : edges) {
        adj[e[0]].push_back({e[1], e[2]});
        adj[e[1]].push_back({e[0], e[2]});
    }

    vector<int> dist(V+1, 1e9), parent(V+1);
    for (int i = 1; i <= V; i++) parent[i] = i;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    dist[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        for (auto [v, wt] : adj[u]) {
            if (d + wt < dist[v]) {
                dist[v] = d + wt;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[V] == 1e9) return {-1};

    vector<int> path;
    int node = V;
    while (parent[node] != node) {
        path.push_back(node);
        node = parent[node];
    }
    path.push_back(1);
    reverse(path.begin(), path.end());
    return path;
}
```

### Complexity Analysis

**Time Complexity:** `O(E log V)` — Dijkstra’s algorithm with PQ for all edge relaxations.

**Space Complexity:** `O(V + E)` — adjacency list, distance, parent, and PQ storage.

---

THE END
