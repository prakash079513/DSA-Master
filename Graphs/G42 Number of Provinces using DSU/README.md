# Number of Provinces using DSU

Author: [Prakash JC](https://prakash079513.github.io/)

## Problem Statement

You are given an **n × n** matrix `isConnected`, where `isConnected[i][j] = 1` means the **i-th** city and **j-th** city are directly connected, and `0` means they are not.

Return the **number of provinces**, where a province is a group of directly or indirectly connected cities.

---

### Intuition

- The problem asks us to count connected components in an undirected graph.
- Each city represents a node, and each connection represents an edge.
- Using **Disjoint Set Union (DSU)**, we can efficiently merge connected cities and count unique provinces.

---

### Approach using DSU (Union-Find)

- Initialize `parent[i] = i` for each city.
- Traverse the `isConnected` matrix:
  - For each pair `(i, j)` where `isConnected[i][j] == 1`, unite the two cities.
- After all unions, count how many nodes are their own parent — this gives the number of provinces.

---

### Code

```cpp
class DSU {
    vector<int> parent, rankv;
public:
    DSU(int n) {
        parent.resize(n);
        rankv.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (x == parent[x]) return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return;
        if (rankv[px] < rankv[py]) parent[px] = py;
        else if (rankv[px] > rankv[py]) parent[py] = px;
        else {
            parent[py] = px;
            rankv[px]++;
        }
    }
};

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        DSU dsu(n);

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (isConnected[i][j]) {
                    dsu.unite(i, j);
                }
            }
        }

        unordered_set<int> provinces;
        for (int i = 0; i < n; i++) {
            provinces.insert(dsu.find(i));
        }

        return provinces.size();
    }
};
```

---

### Complexity Analysis

**Time Complexity:** `O(n² * α(n))` — We traverse the adjacency matrix and perform DSU operations (`α(n)` is the inverse Ackermann function, nearly constant).

**Space Complexity:** `O(n)` — For the parent and rank arrays.

---

THE END
