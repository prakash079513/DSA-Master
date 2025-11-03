# Floyd–Warshall Algorithm

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

Given a weighted directed graph with `n` vertices (possibly containing negative edge weights but **no negative cycles**), find the **shortest distance between every pair of vertices**.

You must return a matrix `dist` where `dist[i][j]` represents the shortest distance from vertex `i` to vertex `j`. If there is **no path**, the distance should remain infinity (or a large value).

---

### Intuition

The Floyd–Warshall algorithm is based on **Dynamic Programming**.

Instead of fixing a single source (like Dijkstra/Bellman-Ford), it tries to **iteratively improve the distance between all pairs** of nodes by considering one intermediate vertex at a time.

At step `k`, we assume that the shortest paths between all pairs of vertices use only vertices `{0, 1, ..., k-1}` as intermediates.

We then check whether vertex `k` can act as a better intermediate node for improving distances between any pair `(i, j)`.

---

### Approach

1. **Initialization:**
   - Start with a distance matrix `dist`, where `dist[i][j]` is the direct edge weight from `i` to `j` if it exists, else infinity.
   - Set `dist[i][i] = 0` for all `i`.
2. **Relaxation through intermediate nodes:**
   - For each vertex `k` (as an intermediate),
     for each vertex `i` (as a source),
     for each vertex `j` (as a destination):
     - Check if going through `k` improves the path from `i` to `j`:
       `if dist[i][k] + dist[k][j] < dist[i][j]`
       then update `dist[i][j] = dist[i][k] + dist[k][j]`.
3. **Handling negative cycles:**
   - After the main loops, if `dist[i][i] < 0` for any vertex `i`, then a **negative cycle** exists.
4. **Output:**
   - The final `dist` matrix will contain the shortest distances between all pairs.

---

### Code

```cpp
void floydWarshall(vector<vector<int>>& dist) {
    int n = dist.size();
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] == 1e9 || dist[k][j] == 1e9) continue;
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}
```

---

### Complexity Analysis

**Time Complexity:** `O(n³)` – Three nested loops iterating over all `(i, j, k)` combinations.

**Space Complexity:** `O(1)` (in-place update on `dist` matrix).

---

THE END
