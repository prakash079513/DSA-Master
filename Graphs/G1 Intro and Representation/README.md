# Graphs

Author: [Prakash JC](https://prakash079513.github.io)

## 1. Introduction

A **Graph** is a way to represent relationships between objects.

- The objects are called **vertices (or nodes)**.
- The relationships are called **edges**.

Example:

- In a **road map**, cities = vertices, roads = edges.
- In a **social network**, people = vertices, friendships = edges.

Formally:

A graph is written as `G = (V, E)`

- `V`: set of vertices.
- `E`: set of edges (pairs of vertices).

---

## 2. Types of Graphs

### (a) **Undirected Graph**

- Edge `(u, v)` means **u is connected to v and v is connected to u**.
- Order does not matter: `(u, v)` = `(v, u)`.
- Example: Friendship network (if A is friend of B, then B is friend of A).

### (b) **Directed Graph (Digraph)**

- Edge `(u, v)` means **u → v**, but not necessarily `v → u`.
- Order matters: `(u, v)` ≠ `(v, u)`.
- Example: Twitter follows (A follows B does not mean B follows A).

---

## 3. Special Graph Types

1. **Weighted Graph:** Each edge has a weight (cost, distance, time, etc.).
   - Example: Road between cities with distance in km.
2. **Unweighted Graph:** Only connections matter (no weights).
   - Example: Social network connections.
3. **Connected Graph:** There is a path between every pair of vertices.
4. **Disconnected Graph:** Some vertices cannot be reached from others.
5. **Cyclic Graph:** Contains at least one cycle (a path that starts and ends at the same vertex).
6. **Acyclic Graph:** Contains no cycle.
   - **Tree** is a special acyclic connected graph.

---

## 4. Basic Terminology

1. **Vertex (Node):** A point in the graph (like `1, 2, 3 … n`).
2. **Edge:** A line connecting two vertices.
3. **Degree of a vertex:**
   - Number of edges touching that vertex.
   - For **undirected graph**: Sum of degrees of all vertices = `2 * E`.
   - For **directed graph**:
     - **In-degree:** Number of incoming edges.
     - **Out-degree:** Number of outgoing edges.
4. **Path:** A sequence of vertices where each consecutive pair has an edge.
   - Example: Path `1 → 2 → 3`.
5. **Simple Path:** Path with no repeated vertex.
6. **Cycle:** Path where the first and last vertex are same.

---

## 5. Sparse vs Dense Graphs

- A graph with **few edges compared to maximum possible edges** = **Sparse graph**.
- A graph with **edges close to maximum possible** = **Dense graph**.

Maximum possible edges:

- Undirected: `n * (n - 1) / 2`
- Directed: `n * (n - 1)`

Example:

- `n = 5`
  - Maximum edges (undirected) = `5 * 4 / 2 = 10`
  - If only 3 edges → Sparse
  - If 9 edges → Dense

---

## 6. Representing Graphs

We usually need to store graphs in programs. Two common ways:

### (a) Adjacency Matrix

- A 2D `n × n` matrix.
- `adj[u][v] = 1` if there is an edge between `u` and `v`.
- For **undirected graph**, mark both `adj[u][v]` and `adj[v][u]`.

Advantages:

- Easy to implement.
- Checking if edge exists is `O(1)`.

Disadvantages:

- Uses `O(n²)` space, even if graph has very few edges.

### Code (Adjacency Matrix)

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1, vector<int>(n + 1, 0));

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u][v] = 1;
        adj[v][u] = 1;  // undirected
    }

    // Print adjacency matrix
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << adj[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
```

---

### (b) Adjacency List

- Each vertex stores a **list of its neighbors**.
- Implemented using `vector<vector<int>>`.

Advantages:

- Uses less memory (`O(n + m)`).
- Efficient for sparse graphs.

Disadvantages:

- Checking if a particular edge exists takes longer (`O(degree(u))`).

### Code (Adjacency List)

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);  // undirected
    }

    // Print adjacency list
    for (int i = 1; i <= n; i++) {
        cout << i << ": ";
        for (int v : adj[i]) {
            cout << v << " ";
        }
        cout << "\n";
    }
    return 0;
}
```

---

## 7. Complexity Comparison

| Representation   | Space      | Edge Check  | Iterating Neighbors |
| ---------------- | ---------- | ----------- | ------------------- |
| Adjacency Matrix | `O(n²)`    | `O(1)`      | `O(n)`              |
| Adjacency List   | `O(n + m)` | `O(deg(u))` | `O(deg(u))`         |

Rule of Thumb:

- Use **Adjacency Matrix** if graph is **dense** or `n` is small.
- Use **Adjacency List** if graph is **sparse** or `n` is large.

---

THE END
