# Number of Ways to Arrive at Destination

**Author:** [Prakash JC](https://prakash079513.github.io/)

## Problem Statement

You are given `n` intersections (0 to n-1) connected by bidirectional roads represented by `roads[i] = [u, v, time]`, where `time` is the travel time between intersections `u` and `v`.

You must determine **the number of distinct ways** to reach intersection `n - 1` from intersection `0` in the **minimum possible travel time**.

Return the count **modulo (1e9 + 7)**.

**Example:**

Input:

`n = 7`, `m = 10`

`roads = [[0,6,7],[0,1,2],[1,2,3],[1,3,3],[6,3,3],[3,5,1],[6,5,1],[2,5,1],[0,4,5],[4,6,2]]`

Output: `4`

Explanation:

Shortest time = 7 minutes.

Four shortest paths are:

- 0 → 6
- 0 → 4 → 6
- 0 → 1 → 2 → 5 → 6
- 0 → 1 → 3 → 5 → 6

---

### Intuition

This is a **modified Dijkstra’s algorithm** problem.

- We must find both the **shortest distance** and the **number of ways** to reach each node using that shortest distance.
- When we find a new shorter path, we **update both distance and count**.
- When we find another path of the same distance, we **add to the count** for that node.

---

### Approach

1. Create an adjacency list `adj` where each edge stores `(neighbor, time)`.
2. Use Dijkstra’s algorithm with a **min-heap (priority_queue)**.
3. Maintain:
   - `dist[i]`: shortest distance from source (0) to node `i`.
   - `ways[i]`: number of ways to reach node `i` using shortest distance.
4. Initialize:
   - `dist[0] = 0`, `ways[0] = 1`.
5. For each popped `(time, node)` from the heap:
   - For every neighbor `(adjNode, wt)`:
     - If a **shorter distance** is found → update `dist` and assign `ways[adjNode] = ways[node]`.
     - If an **equal distance** is found → add `ways[node]` to `ways[adjNode]`.
6. Finally, return `ways[n-1] % (1e9 + 7)`.

---

### Code

```cpp
#define ll long long
const int MOD = 1e9 + 7;

int countPaths(int n, vector<vector<int>>& roads) {
    vector<pair<int, int>> adj[n];
    for (auto &r : roads) {
        adj[r[0]].push_back({r[1], r[2]});
        adj[r[1]].push_back({r[0], r[2]});
    }

    vector<ll> dist(n, LLONG_MAX), ways(n, 0);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

    dist[0] = 0;
    ways[0] = 1;
    pq.push({0, 0});

    while (!pq.empty()) {
        auto [time, node] = pq.top();
        pq.pop();

        if (time > dist[node]) continue;

        for (auto [nei, wt] : adj[node]) {
            ll newTime = time + wt;

            if (newTime < dist[nei]) {
                dist[nei] = newTime;
                ways[nei] = ways[node];
                pq.push({newTime, nei});
            } else if (newTime == dist[nei]) {
                ways[nei] = (ways[nei] + ways[node]) % MOD;
            }
        }
    }

    return ways[n - 1] % MOD;
}
```

---

### Complexity Analysis

**Time Complexity:** `O(E log V)`

- Dijkstra’s algorithm with a min-heap on `E` edges and `V` nodes.

**Space Complexity:** `O(V + E)`

- For adjacency list, distance, and ways arrays.

This is the **optimal and most accepted** approach for this problem.

---

THE END
