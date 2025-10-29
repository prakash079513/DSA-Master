## Dijkstra’s Algorithm using Set

Author: [Prakash JC](https://prakash079513.github.io)

### Approach

- Instead of a priority queue, use a **set of pairs (distance, node)** to always fetch the node with the smallest current distance
- Set automatically maintains elements in increasing order and allows **deletion** of outdated entries (which PQ doesn’t)
- Each time a shorter path is found, remove the older entry (if exists) and insert the new `(distance, node)` pair

### Why Use Set

- Set allows **efficient decrease-key** operation by erasing the old `(dist, node)` before inserting the new one
- Ensures there’s only one valid distance entry per node at a time
- Useful when we need precise control over updates, unlike PQ which may keep stale values

---

### Code

```cpp
vector<int> dijkstra(int V, vector<vector<pair<int,int>>> &adj, int src) {
    vector<int> dist(V, 1e9);
    dist[src] = 0;

    set<pair<int,int>> st;
    st.insert({0, src});

    while (!st.empty()) {
        auto it = *(st.begin());
        int node = it.second;
        int d = it.first;
        st.erase(it);

        for (auto &x : adj[node]) {
            int nei = x.first;
            int wt = x.second;

            if (d + wt < dist[nei]) {
                if (dist[nei] != 1e9)
                    st.erase({dist[nei], nei});

                dist[nei] = d + wt;
                st.insert({dist[nei], nei});
            }
        }
    }
    return dist;
}
```

### Complexity Analysis

**Time Complexity:** `O(E log V)` — insertion and deletion in set are `O(log V)` for each edge relaxation.

**Space Complexity:** `O(V + E)` — adjacency list + set + distance array.

**Note:**

Both **set** and **priority queue** give the same asymptotic complexity, but:

- PQ is slightly **faster** in practice.
- Set version allows explicit **deletion** (better when handling dynamic updates).

---

THE END
