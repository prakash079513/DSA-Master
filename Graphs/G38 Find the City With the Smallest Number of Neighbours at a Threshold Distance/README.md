# Find the City With the Smallest Number of Neighbours at a Threshold Distance

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

You are given `n` cities numbered `0` to `n - 1` and a list of weighted bidirectional roads represented as `edges[i] = [fromi, toi, weighti]`.

You are also given a **distance threshold** value.

You must determine the **city** that can reach the **fewest number of other cities** within a distance less than or equal to the threshold.

If multiple cities have the same smallest count, return the **city with the largest number**.

---

### Approach

This problem is a direct application of the **Floyd–Warshall algorithm** (All-Pairs Shortest Path).

Since we need distances between **every pair of cities**, we compute them once and then count reachable cities per node.

1. **Initialize distance matrix**
   - Create a matrix `dist[n][n]`, where `dist[i][j]` = direct edge weight if it exists, else infinity (`1e9`).
   - Set diagonal elements `dist[i][i] = 0`.
2. **Compute All-Pairs Shortest Paths (Floyd–Warshall)**
   - For each intermediate city `k`, update the shortest distance:
     `dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])`.
3. **Count reachable cities for each node**
   - For each city `i`, count how many cities `j` satisfy `dist[i][j] <= threshold`.
4. **Find the city with the smallest count**
   - Track the city with the minimum reachable count.
   - In case of a tie, choose the **city with the greater index**.

---

### Code

```cpp
int findTheCity(int n, vector<vector<int>>& edges, int threshold) {
    vector<vector<int>> dist(n, vector<int>(n, 1e9));

    // Step 1: Initialize distances
    for (int i = 0; i < n; i++) dist[i][i] = 0;
    for (auto &e : edges) {
        int u = e[0], v = e[1], w = e[2];
        dist[u][v] = w;
        dist[v][u] = w;
    }

    // Step 2: Floyd–Warshall algorithm
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] == 1e9 || dist[k][j] == 1e9) continue;
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    // Step 3: Count reachable cities
    int minReach = n + 1, city = -1;
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (dist[i][j] <= threshold) count++;
        }
        if (count <= minReach) {
            minReach = count;
            city = i; // choose greater index in tie
        }
    }

    return city;
}
```

---

### Complexity Analysis

**Time Complexity:** `O(n³)` – Due to Floyd–Warshall triple nested loops.

**Space Complexity:** `O(n²)` – For storing the distance matrix.

---

THE END
