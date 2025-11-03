# Bellman-Ford Algorithm

**Author:** [Prakash JC](https://prakash079513.github.io/)

## Problem Statement

Given a graph with `V` vertices and `E` edges (which can include **negative edge weights**), find the **shortest distance** from a given **source vertex** to all other vertices.

If the graph contains a **negative weight cycle**, report its presence (as shortest paths cannot be defined in such cases).

---

### Intuition

The **Bellman-Ford algorithm** is based on the **principle of relaxation** — repeatedly updating the shortest distance estimate for every edge.

- Unlike Dijkstra’s, it works even with **negative weights**, since it does not rely on a priority queue or greedy selection.
- By performing `V - 1` relaxation passes, all shortest paths (in absence of negative cycles) are guaranteed to stabilize.
- A **Vth pass** can detect a **negative weight cycle** if any distance can still be relaxed.

---

### Approach

1. Initialize distance array `dist[]` with `∞`, and set `dist[src] = 0`.
2. For `i = 1` to `V - 1`:
   - Iterate over all edges `(u, v, wt)`.
   - If `dist[u] + wt < dist[v]`, update `dist[v] = dist[u] + wt`.
   - Repeat this process to propagate minimum distances across edges.
3. Run one extra iteration (Vth):
   - If any distance can still be updated, **a negative weight cycle exists**.
4. Return the distance array if no negative cycle is detected.

---

### Code

```cpp
vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
    vector<int> dist(V, 1e8);
    dist[src] = 0;

    // Step 1: Relax all edges (V - 1) times
    for (int i = 0; i < V - 1; i++) {
        for (auto &e : edges) {
            int u = e[0], v = e[1], wt = e[2];
            if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
                dist[v] = dist[u] + wt;
            }
        }
    }

    // Step 2: Check for negative weight cycles
    for (auto &e : edges) {
        int u = e[0], v = e[1], wt = e[2];
        if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
            cout << "Negative Weight Cycle Detected" << endl;
            return {-1};
        }
    }

    return dist;
}
```

---

### Complexity Analysis

**Time Complexity:** `O(V * E)`

- Each of the `V - 1` passes processes all `E` edges.

**Space Complexity:** `O(V)`

- For storing the distance array.

---

THE END
