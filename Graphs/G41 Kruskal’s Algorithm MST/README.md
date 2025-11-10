# Kruskal’s Algorithm MST

**Author:** [Prakash JC](https://prakash079513.github.io/)

### Introduction

Kruskal’s Algorithm is a **greedy** algorithm used to find the **Minimum Spanning Tree (MST)** of a connected, weighted, and undirected graph.

It selects edges in increasing order of their weights and adds them to the MST **only if** an u and v of an edge do not belong to the same set or component or also if they do not form a cycle.

The cycle check is efficiently handled using the **Disjoint Set Union (DSU)** data structure.

---

### Intuition

- We want the minimum total weight while connecting all vertices.
- The MST must connect all nodes with exactly `n-1` edges and no cycles.
- Kruskal’s algorithm does this by:
  - Sorting all edges by weight.
  - Picking the smallest edge that connects **two different components**.
  - Using **Disjoint Set Union (DSU)** to efficiently detect cycles.

---

### Approach

1. Sort all edges by ascending weight.
2. Initialize a Disjoint Set structure for all vertices.
3. Traverse through the sorted edges:
   - If the current edge connects two **different components**, include it in the MST and unite those components.
   - Otherwise, skip the edge (it would form a cycle).
4. Continue until `n-1` edges are included in the MST.
5. Return the total MST weight.

---

### Code

```cpp
class DisjointSet {
    vector<int> parent, size;
public:
    DisjointSet(int n) {
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        for (int i = 0; i <= n; i++) parent[i] = i;
    }

    int findParent(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findParent(parent[node]); // Path compression
    }

    void unionBySize(int u, int v) {
        int pu = findParent(u);
        int pv = findParent(v);
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
    int spanningTree(int n, vector<vector<int>> &edges) {
        vector<pair<int, pair<int, int>>> edgeList;
        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            edgeList.push_back({w, {u, v}});
        }

        sort(edgeList.begin(), edgeList.end());
        DisjointSet ds(n);
        int mstWeight = 0;

        for (auto &it : edgeList) {
            int w = it.first;
            int u = it.second.first;
            int v = it.second.second;

            if (ds.findParent(u) != ds.findParent(v)) {
                mstWeight += w;
                ds.unionBySize(u, v);
            }
        }

        return mstWeight;
    }
};
```

---

### Complexity Analysis

**Time Complexity:**

- Sorting edges: `O(E log E)`
- DSU operations: `O(E * α(N))` (almost constant)
  **Overall:** `O(E log E)`

**Space Complexity:**

- DSU parent and size arrays: `O(N)`
- Edge storage: `O(E)`
  **Overall:** `O(N + E)`

---

THE END
