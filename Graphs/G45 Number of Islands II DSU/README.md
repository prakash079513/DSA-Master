# Number of Islands II — Online Queries (DSU Approach)

Author: [Prakash JC](https://prakash079513.github.io/)

## Problem Statement

You are given an initially water-filled grid of size `n × m` (all 0s).

Each operation in array `A` converts a water cell `(r, c)` into **land (1)**.

After each operation, you must return the **number of islands** present in the matrix.

An island is a group of 1s connected 4-directionally (up, down, left, right).

### Example

**Input:**

```
n = 4, m = 5,
A = {{0,0},{0,0},{1,1},{1,0},{0,1},{0,3},
     {1,3},{0,4},{3,2},{2,2},{1,2},{0,2}}
```

**Output:**

```
1 1 2 1 1 2 2 2 3 3 1 1
```

**Explanation:**

- After each operation, land cells may merge to form islands.
- The DSU efficiently tracks the merging of connected components (islands).

---

### Intuition

- Treat each land cell as a **node** in a graph.
- Two nodes belong to the same island if they are **connected** 4-directionally.
- As new lands appear, they might:
  - Create a new island.
  - Merge with neighboring existing islands.
- Use **Disjoint Set Union (DSU)** to dynamically merge islands and count connected components in `O(α(n*m))` time per operation.

---

### Approach

### Step-by-step logic

- Initialize DSU for `n*m` cells.
- Maintain a matrix `vis[n][m]` initialized with 0 (water).
- Maintain a counter `count` for the number of islands.
- For each query `(r, c)`:
  1. If the cell is already land → push current count and continue.
  2. Mark cell as land (`vis[r][c] = 1`) → increment `count` (new island).
  3. For each of 4 neighbors `(r±1, c±1)`:
     - If within bounds and land:
       - If their parents differ → union them and decrement `count`.
  4. Push the current `count` to the result vector.

---

### Code

```cpp
class DisjointSet {
public:
    vector<int> parent, size;
    DisjointSet(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int findUPar(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findUPar(parent[node]);
    }

    void unionBySize(int u, int v) {
        int pu = findUPar(u), pv = findUPar(v);
        if (pu == pv) return;
        if (size[pu] < size[pv]) {
            parent[pu] = pv;
            size[pv] += size[pu];
        } else {
            parent[pv] = pu;
            size[pu] += size[pv];
        }
    }
};

class Solution {
public:
    vector<int> numOfIslands(int n, int m, vector<vector<int>> &operators) {
        DisjointSet ds(n * m);
        int count = 0;
        vector<int> ans;
        vector<vector<int>> vis(n, vector<int>(m, 0));
        vector<int> dr = {-1, 0, 1, 0};
        vector<int> dc = {0, 1, 0, -1};

        for (auto &op : operators) {
            int r = op[0], c = op[1];
            if (vis[r][c] == 1) {
                ans.push_back(count);
                continue;
            }
            vis[r][c] = 1;
            count++;

            int node = r * m + c;
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i], nc = c + dc[i];
                if (nr >= 0 && nr < n && nc >= 0 && nc < m && vis[nr][nc] == 1) {
                    int adjNode = nr * m + nc;
                    if (ds.findUPar(node) != ds.findUPar(adjNode)) {
                        ds.unionBySize(node, adjNode);
                        count--;
                    }
                }
            }
            ans.push_back(count);
        }
        return ans;
    }
};
```

### Complexity Analysis

**Time Complexity:** `O(k * 4 * α(n*m))`

- For `k` operations, each union/find takes nearly constant time.

**Space Complexity:** `O(n*m)`

- For DSU arrays and visited matrix.

---

THE END
