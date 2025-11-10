# Number of Operations to Make Network Connected — DSU

Author: [Prakash JC](https://prakash079513.github.io/)

## Problem Statement

You are given an undirected graph with `n` vertices and `m` edges.

In one operation, you can **remove one edge** from anywhere and **add it between any two vertices**.

Your task is to find the **minimum number of operations** required to make the graph **connected**.

If it is **not possible**, return `-1`.

---

### Example

```
Input:
n = 6
edges = [[0,1], [0,2], [0,3], [1,2]]

Output: 2

Explanation:
- There are 6 nodes but only 4 edges.
- There are enough extra edges (1 redundant) to connect the 3 remaining components.
- So, 2 operations are required to connect all.
```

---

### Intuition

- The graph is connected if all nodes belong to a **single connected component**.
- Using **Disjoint Set Union (DSU)**, we can efficiently:
  - Count how many **components** exist.
  - Identify how many **extra edges** are available (edges connecting already-connected vertices).
- If the number of extra edges ≥ (components - 1), we can make the graph connected.

---

### Approach Using DSU (Union-Find)

- Initialize a Disjoint Set (DSU) with `n` nodes.
- For each edge `(u, v)`:
  - If `u` and `v` are already connected → it’s an **extra edge**.
  - Else → union the two nodes.
- After processing all edges:
  - Count how many **independent components** remain.
  - Minimum operations required = `components - 1`.
  - If extra edges ≥ required operations → return that number.
  - Else → return `1`.

---

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

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
    int makeConnected(int n, vector<vector<int>>& edges) {
        DisjointSet ds(n);
        int extra = 0;

        for (auto &it : edges) {
            int u = it[0], v = it[1];
            if (ds.findUPar(u) != ds.findUPar(v)) ds.unionBySize(u, v);
            else extra++;
        }

        int components = 0;
        for (int i = 0; i < n; i++) {
            if (ds.parent[i] == i) components++;
        }

        int ops = components - 1;
        if (extra >= ops) return ops;
        return -1;
    }
};

int main() {
    vector<vector<int>> edges = {{0,1},{0,2},{0,3},{1,2}};
    int n = 6;
    Solution s1;
    cout << s1.makeConnected(n, edges);
    return 0;
}
```

---

### Complexity Analysis

**Time Complexity:** `O(E * α(V))` — Each DSU operation runs in nearly constant time.

**Space Complexity:** `O(V)` — For storing parent and size arrays.

---

THE END
