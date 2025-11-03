# Cheapest Flights Within K Stops

Author: [Prakash JC](https://prakash079513.github.io/)

## Problem Statement

You are given `n` cities numbered `0` to `n-1`, and a list of flights where each `flights[i] = [from, to, price]` indicates a direct flight from `from` → `to` costing `price`. You are also given integers `src`, `dst`, and `k`. Return the **cheapest price** to travel from `src` to `dst` using at most `k` stops (i.e., at most `k+1` flights). If no such route exists, return `-1`. ([LeetCode](https://leetcode.com/problems/cheapest-flights-within-k-stops/description))

---

### Takeaways

- Stops is the main priority not the distances. Normal dijkstra wont track the stops well. So push stops, node, dist into the queue. PQ adds extra logn factor.
- Queue is sufficient as everytime the value of stops is increasing by only 1.
- Even if stops == k we have to push into the queue i.e., push as long as stops ≤ k.
- Make sure to push the dist as d + w instead of dist[v], there was some global issue. Just updat with the new cost only.

---

## Editorial

### Intuition

We need the minimum-cost path from `src` → `dst`, but constrained by **at most** `k` stops. Traditional Dijkstra ignores the stop‐limit, and plain BFS might ignore cost; we need to consider both cost _and_ number of stops.

## Approach Using Queue

- Model the problem as a directed weighted graph using an adjacency list.
- Perform a **BFS-like traversal** where each state tracks:
  - The current city
  - The total cost so far
  - The number of stops taken
- Maintain a distance array `dist` storing the minimum cost to reach each city.
- Push `(stops, node, cost)` into the queue and explore neighbors only if `stops ≤ k`.
- Relax edges: if `d + w < dist[v]`, update and push `(stops + 1, v, new_cost)` into the queue.
- At the end, return `dist[dst]` if reachable, else `1`.

This mimics Dijkstra but limits the number of layers (stops) instead of using a priority queue.

---

### Code

```cpp
int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    vector<vector<pair<int,int>>> adj(n);
    for(auto &f : flights)
        adj[f[0]].push_back({f[1], f[2]});

    vector<int> dist(n, 1e9);
    dist[src] = 0;

    queue<tuple<int,int,int>> q; // stops, node, cost
    q.push({0, src, 0});

    while(!q.empty()) {
        auto [stops, u, cost] = q.front();
        q.pop();

        if(stops > k) continue;

        for(auto [v, w] : adj[u]) {
            if(cost + w < dist[v]) {
                dist[v] = cost + w;
                q.push({stops + 1, v, cost + w}); // VIP: Push cost + w only.
            }
        }
    }

    return dist[dst] == 1e9 ? -1 : dist[dst];
}
```

### Complexity Analysis

**Time Complexity:** `O(E * K)` — each edge can be relaxed at most `K+1` times.

**Space Complexity:** `O(V + E)` — adjacency list and queue storage.

---

## Approach Using PQ

1. Build adjacency list: for each flight `[u,v,w]`, add `u → (v,w)`.
2. Use a **min-heap priority queue** storing tuples `(cost, city, stopsUsed)`.
3. Use a `costs[city][stops]` tracking table, or a best-cost array with stops filter.
4. Push `(0, src, 0)` into PQ.
5. While PQ not empty:
   - Pop `(cost, u, stops)` with smallest cost.
   - If `u == dst`, return `cost`.
   - If `stops > k`, continue.
   - For each neighbor `(v, w)` of `u`:
     - `newCost = cost + w`.
     - If `newCost < bestCost[v][stops+1]`: update and push `(newCost, v, stops+1)`.
6. If loop ends without reaching `dst`, return `1`.

---

### Code

```cpp
int findCheapestPrice(int n, vector<vector<int>>& flights,
                        int src, int dst, int K) {
    vector<vector<pair<int,int>>> adj(n);
    for (auto &f : flights) {
        adj[f[0]].push_back({f[1], f[2]});
    }

    const int INF = 1e9;
    vector<vector<int>> best(n, vector<int>(K+2, INF));
    // best[v][s] = minimum cost to reach v using s flights

    priority_queue<tuple<int,int,int>,
                    vector<tuple<int,int,int>>,
                    greater<tuple<int,int,int>>> pq;
    pq.push({0, src, 0});
    best[src][0] = 0;

    while (!pq.empty()) {
        auto [cost, u, flightsUsed] = pq.top();
        pq.pop();
        if (u == dst) return cost;
        if (flightsUsed == K+1) continue;

        for (auto &edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            int newCost = cost + w;
            if (newCost < best[v][flightsUsed + 1]) {
                best[v][flightsUsed + 1] = newCost;
                pq.push({newCost, v, flightsUsed + 1});
            }
        }
    }
    return -1;
}
```

### Complexity Analysis

**Time Complexity:** `O((K+1) * (V + E) log V)` — each state `(city, flightsUsed)` is pushed/popped at most once per stop-level.

**Space Complexity:** `O(V * (K+2) + E)` — adjacency list + best costs table + PQ.

---

## Best Approach **Bellman-Ford style**

- This approach is a **Dynamic Programming (Bellman-Ford style)** solution adapted for the K-stop constraint.
- Maintain two arrays:
  - `prevLevelPrices`: minimum cost to reach each city using at most `stops` flights.
  - `nextLevelPrices`: updated costs for the next iteration (stops + 1).
- Initialize `prevLevelPrices[src] = 0` and others to `INT_MAX`.
- For `k + 1` iterations:
  - Traverse all edges `(u → v, price)`.
  - If `u` is reachable (`prevLevelPrices[u] != INT_MAX`), try relaxing:
    `nextLevelPrices[v] = min(nextLevelPrices[v], prevLevelPrices[u] + price)`.
- After all iterations, the destination cost in `prevLevelPrices[dst]` gives the minimum price within `k` stops.
- If it's still `INT_MAX`, return `1`.

---

### Code

```cpp
int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    vector<vector<pair<int,int>>> adj(n);
    for (auto &flight : flights)
        adj[flight[0]].push_back({flight[1], flight[2]});

    vector<int> prevLevelPrices(n, INT_MAX);
    prevLevelPrices[src] = 0;

    for (int stops = 0; stops <= k; stops++) {
        vector<int> nextLevelPrices = prevLevelPrices;

        for (int u = 0; u < n; ++u) {
            if (prevLevelPrices[u] == INT_MAX) continue;

            for (auto &[v, price] : adj[u]) {
                if (prevLevelPrices[u] + price < nextLevelPrices[v])
                    nextLevelPrices[v] = prevLevelPrices[u] + price;
            }
        }

        prevLevelPrices = nextLevelPrices;
    }

    return prevLevelPrices[dst] == INT_MAX ? -1 : prevLevelPrices[dst];
}
```

### Complexity Analysis

**Time Complexity:** `O(K * E)` — every iteration processes all edges for up to `k + 1` stops.

**Space Complexity:** `O(V)` — only two arrays are used to store costs for current and next levels.

---

### Comparison of All Three Methods

| Method                              | Concept                    | When to Prefer                                  | Pros                             | Cons                                    |
| ----------------------------------- | -------------------------- | ----------------------------------------------- | -------------------------------- | --------------------------------------- |
| **Priority Queue (Dijkstra-based)** | Greedy shortest path       | Best when we need globally minimal cost quickly | Fast in sparse graphs            | Harder to limit stops precisely         |
| **Queue (BFS-based)**               | Layered BFS on stops       | Easier to implement for small `k`               | Simple and intuitive             | May do redundant relaxations            |
| **DP (Bellman-Ford style)**         | Relax edges for `k` layers | Most reliable and clean for `k` constraint      | Deterministic and easy to reason | Slightly slower than PQ on large graphs |

**Best Choice:** **DP (Bellman-Ford style)** for bounded `k` (as in this problem).

It’s clean, avoids over-relaxation, and guarantees correctness for exactly `k` stops.

---

THE END
