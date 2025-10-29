## Dijkstra’s Algorithm using Priority Queue

Author: [Prakash JC](https://prakash079513.github.io)

### Note:

- Used for shortest path in graphs with **non-negative** edge weights
- Stop processing outdated states by checking if the popped distance is greater than the current stored distance

### Approach

- Declare a distance array of size V initialized with 1e9.
- Initialize the dist of source node with 0.
- Declare a **min-heap priority queue of pair of `dist, node`** as we need min dist first, if dist is same, early node first.
- Push the source dist and node into pq.
- While pq is not empty:
  - Take out the element.
  - For every neighbor:
    - If the dist to reach it is less than the val in dist array stored to reach it:
      - Update dist
      - Push into pq
- Return the final dist array.

### Why Priority Queue

- We want the **next node with the smallest tentative distance**
- A normal queue may lead to unnecessary processing of longer paths first
- Priority queue ensures optimal greedy choice at every step

---

### Code

```cpp
vector<int> dijkstra(int V, vector<vector<pair<int,int>>> &adj, int src) {
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq; // Do not forget greater of pair.
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, node] = pq.top();
        pq.pop();

        if (d > dist[node]) continue; // Skip redudant calcs. Check note above.

        for (auto &it : adj[node]) {
            int next = it.first;
            int wt = it.second;

            if (d + wt < dist[next]) {
                dist[next] = d + wt;
                pq.push({dist[next], next});
            }
        }
    }
    return dist;
}
```

### Complexity Analysis

**Time Complexity:** `O(E log V)` — each edge relaxation may push into PQ, each push/pop is `log V`.

**Space Complexity:** `O(V + E)` — adjacency list + PQ storage + distance array.

**Derivation:**

- PQ operations dominate
- Every edge can trigger a decrease-key simulation by pushing a new pair
- Total push operations ≤ `E` so `E log V`

---

THE END
