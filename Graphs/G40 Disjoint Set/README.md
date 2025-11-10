# Disjoint Set (Union-Find Data Structure)

**Author:** [Prakash JC](https://prakash079513.github.io/)

### Introduction

The **Disjoint Set Union (DSU)** or **Union-Find** data structure is one of the most fundamental and powerful tools in graph algorithms.

It helps efficiently manage a collection of **non-overlapping sets** and perform two key operations:

1. **Find:** Determine which set a particular element belongs to.
2. **Union:** Merge two sets into one.

Time complexity is almost constant.

---

### Aim

The main goal of DSU is to quickly check and merge connectivity relationships between elements — for example:

- Checking if two vertices belong to the same connected component in a graph.
- Building a **Minimum Spanning Tree (Kruskal’s Algorithm)**.
- Detecting cycles in undirected graphs.
- Handling dynamic connectivity problems.

---

### Core Operations

1. **Find Parent (Find):**
   - Returns the “ultimate parent” or representative of a set or root parent.
   - Uses **path compression** to flatten the structure for faster future queries. That is, to find the root parent of a random curr node: for one time you go all the way up and find the root parent. Now store the parent of this curr node as root parent. So next time it will be easier.
2. **Union:**
   - Combines two disjoint sets into one.
   - It is a function that takes two nodes as parameters i.e., `union(int u, int v)`.
   - **Note:** It combines the root parents of u and v i.e, link is pu — pv but not u — v. What is connected to what is discussed below.
   - Can be implemented in two optimized ways:
     - **Union by Rank**
     - **Union by Size**

---

### Concept for Union Rank

- Each node has a **rank**, roughly representing tree height.
- When performing a union for u and v:
  - Find the root parents of u and v. Say pu and pv.
  - **Note:** The root with **smaller rank** is attached under the root with **larger rank**. Because, Attaching a **smaller tree under a larger one** avoids unnecessary height increase which in turn is a burden to find root parent for the bottom nodes.
  - If rank of pu is less than rank of pv, then the pu set is attached to pv set, i.e., parent of pu is pv.
  - Similarly, If rank of pv is less than rank of pu, then the pv set is attached to pu set, i.e., parent of pv is pu.
  - Mainly, if ranks are equal, attach one to the other(usually pv to pu) and **increase rank** of the new root(generally pu) by 1.

---

### Why Attach Smaller to Larger?

When merging two sets:

- Attaching a **smaller tree under a larger one** avoids unnecessary height increase.
- The larger tree’s structure dominates, ensuring minimal additional depth.
- This leads to almost constant-time operations (`O(α(n))`, where α(n) is the inverse Ackermann function — practically ≤ 4).

## Implementation

### **Define the Class and Arrays**

We use a class because it keeps everything organized.

We define two arrays:

1. `parent[i]` → stores the parent of node `i`
2. `rank[i]` → stores the approximate height of the tree rooted at `i` .

```cpp
class DisjointSet {
public:
    vector<int> parent, rank;
```

### **Initialize in the Constructor**

- Initialize both arrays.
- Every node is initially its own parent → `parent[i] = i`
- Every node’s rank starts as `0`.

```cpp
DisjointSet(int n) {
    parent.resize(n + 1);
    rank.resize(n + 1, 0);

    for (int i = 0; i <= n; i++) {
        parent[i] = i;
    }
}
```

---

### **Find Function — `findUPar()`**

- Finds the **ultimate parent (root)** of a node.
- Uses **path compression** to make future finds faster by directly linking nodes to their root.

**Code Snippet:**

```cpp
int findUPar(int node) {
    if (parent[node] == node)
        return node;
    return parent[node] = findUPar(parent[node]);  // path compression
}
```

---

### **Union by Rank — `unionByRank()`**

- Finds the ultimate parents of both nodes.
- Attaches the tree with **smaller rank** under the one with **larger rank**.
- If both ranks are equal → attach one to another and **increase** the new root’s rank by 1.

```cpp
void unionByRank(int u, int v) {
    int pu = findUPar(u);
    int pv = findUPar(v);

    if (pu == pv) return; // already in same set

    if (rank[pu] < rank[pv]) {
        parent[pu] = pv;
    }
    else if (rank[pu] > rank[pv]) {
        parent[pv] = pu;
    }
    else {
        parent[pv] = pu;
        rank[pu]++;  // increase rank if both same
    }
}
```

---

### **Union by Size — `unionBySize()`**

- Instead of rank, we maintain a `size` array (number of nodes in each set).
- Attach the **smaller-size** tree under the **larger-size** tree.
- Update the size of the new root.

```cpp
vector<int> size;

DisjointSet(int n, bool useSize) {
    parent.resize(n + 1);
    size.resize(n + 1, 1);
    for (int i = 0; i <= n; i++) {
        parent[i] = i;
    }
}

void unionBySize(int u, int v) {
    int pu = findUPar(u);
    int pv = findUPar(v);

    if (pu == pv) return;

    if (size[pu] < size[pv]) {
        parent[pu] = pv;
        size[pv] += size[pu];
    } else { // since for both the other cases we need to increment pu size, one else block is enough
        parent[pv] = pu;
        size[pu] += size[pv];
    }
}
```

---

### Why Optimizations are Needed

Without optimization, the tree representing sets can become tall, causing `O(n)` find/union time.

To optimize:

- **Path Compression** ensures the tree height remains nearly constant.
- **Union by Rank/Size** ensures smaller trees are always attached under larger ones, **minimizing height growth.**

---

### Final Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
public:
    vector<int> rank, parent, size;

    // Constructor
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        size.resize(n + 1, 1);   // size initialized to 1
        parent.resize(n + 1);
        for (int i = 0; i <= n; i++)
            parent[i] = i;
    }

    // Find with path compression
    int findParent(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findParent(parent[node]);
    }

    // Union by Rank
    void unionByRank(int u, int v) {
        int pu = findParent(u);
        int pv = findParent(v);
        if (pu == pv) return; // already in same set

        if (rank[pu] < rank[pv]) parent[pu] = pv;
        else if (rank[pv] < rank[pu]) parent[pv] = pu;
        else {
            parent[pv] = pu;
            rank[pu]++;
        }
    }

    // Union by Size
    void unionBySize(int u, int v) {
        int pu = findParent(u);
        int pv = findParent(v);
        if (pu == pv) return; // already in same set

        if (size[pu] < size[pv]) {
            parent[pu] = pv;
            size[pv] += size[pu];
        } else {
            parent[pv] = pu;
            size[pu] += size[pv];
        }
    }
};

int main() {
    DisjointSet ds(7);

    // Using union by rank
    ds.unionByRank(1, 2);
    ds.unionByRank(2, 3);
    ds.unionByRank(4, 5);
    ds.unionByRank(6, 7);
    ds.unionByRank(5, 6);

    cout << (ds.findParent(3) == ds.findParent(7) ? "Same Component" : "Different Components") << endl;

    ds.unionByRank(3, 7);
    cout << (ds.findParent(3) == ds.findParent(7) ? "Same Component" : "Different Components") << endl;

    // Using union by size (example)
    DisjointSet ds2(7);
    ds2.unionBySize(1, 2);
    ds2.unionBySize(2, 3);
    ds2.unionBySize(4, 5);
    ds2.unionBySize(6, 7);
    ds2.unionBySize(5, 6);
    ds2.unionBySize(3, 7);

    cout << (ds2.findParent(3) == ds2.findParent(7) ? "Same Component (Size)" : "Different Components (Size)") << endl;

    return 0;
}
```

---

### Complexity Analysis

**Time Complexity:** `O(4α)` approx as `O(α(n))` — inverse Ackermann function, almost constant per operation.

**Space Complexity:** `O(n)` — for parent and rank arrays.

---

### When to Use Which

| Technique         | Best When                        | Explanation                                                |
| ----------------- | -------------------------------- | ---------------------------------------------------------- |
| **Union by Rank** | Tracking approximate tree height | Conceptually simpler and used in theoretical derivations   |
| **Union by Size** | Tracking component sizes         | More intuitive, often performs slightly better in practice |

---

### **Conclusion:**

Disjoint Set is a highly optimized structure for efficiently managing dynamic connectivity in graphs. With **path compression** and **union optimizations (rank/size)**, all operations effectively run in **amortized constant time**, forming the backbone for algorithms like **Kruskal’s MST**, **connected component detection**, and **network connectivity analysis**.

---

THE END
