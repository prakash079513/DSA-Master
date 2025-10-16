# Breadth First Search (BFS)

Author: [Prakash JC](https://prakash079513.github.io)

## 1. Introduction

**Breadth First Search (BFS)** is a graph traversal algorithm that explores a graph level by level.

- Start from a given source vertex.
- Visit all its neighbors first.
- Then visit the neighbors’ neighbors, and so on.

BFS is widely used in problems like shortest path in unweighted graphs, checking bipartite property, and level-order exploration of nodes.

---

## 2. BFS Approach

1. Maintain a **queue** to store vertices to be explored.
2. Maintain a **visited array** to ensure each vertex is processed only once.
3. Push the starting vertex into the queue and mark it visited.
4. While the queue is not empty:
   - Remove the front element.
   - Add it to the BFS result.
   - Push all its unvisited neighbors into the queue.
5. If the graph is disconnected, repeat this process for all unvisited vertices.

---

## 3. Implementations

## 3.1 BFS using Adjacency List

### Undirected and 0-based node indexing:

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> bfs(int V, vector<vector<int>> adj) {
        vector<int> bfs;
        vector<int> visited(V, 0); // V+1 for 1-baseed.
        queue<int> q;

        visited[0] = 1; // visited[1] = 1; for 1-based.
        q.push(0); // q.push(1); for 1-based.

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            bfs.push_back(node);

            for (int it : adj[node]) {
                if (!visited[it]) {
                    visited[it] = 1;
                    q.push(it);
                }
            }
        }
        return bfs;
    }
};

int main() {
    int V, E;
    cin >> V >> E;

    vector<vector<int>> adj(V); // V+1 for 1-baseed.
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    Solution s;
    vector<int> res = s.bfs(V, adj);

    for (int x : res) cout << x << " ";
    return 0;
}
```

### Changes for 1-based node indexing:

1. `adj` list should be of size `V+1` to accommodate nodes from `1` to `V`.
2. `visited` array list should be of size `V+1` to accommodate nodes from `1` to `V`.
3. Mark `1` as visited and push `1` into the queue.

### Alternate Solution for 1-based:

> **Keep the BFS function as 0-based. BUT, when reading the edge inputs inside the for loop, decrement both `u` and `v` by 1 (`u--` and `v--`) immediately after input. This converts the input from 1-based to 0-based indexing for internal storage.**

### Code

```cpp
for (int i = 0; i < E; i++) {
    int u, v;
    cin >> u >> v;
    u--; v--;                      // convert to 0-based for internal storage
    adj[u].push_back(v);
    adj[v].push_back(u);
}
```

### Directed

All the code remains the same **except**: Remove the line

```cpp
adj[v].push_back(u);
```

---

### Complexity Analysis (for both **undirected** and **directed** graphs)

### **Time Complexity:** `O(V + E)`

- Each vertex is **enqueued and dequeued once:** `O(2V)`
- Each edge is **processed once**:
  - In **undirected graphs**, each edge appears in two adjacency lists: `O(2E)`
  - In **directed graphs**, each edge is stored and processed only once: `O(E)`

**Exact:** `O(2V + 2E)` (undirected), `O(2V + E)` (directed)

**Approximate:** `O(V + E)` for both.

---

### **Space Complexity:** `O(V + E)`

- `visited[]` array → `O(V)`
- `queue` → up to `O(V)` in worst case
- `bfs` result vector → `O(V)`
- `adjacency list` → `O(2E)` (undirected), `O(E)` (directed)

**Exact:** `O(3V + 2E)` (undirected), `O(3V + E)` (directed)

**Approximate:** `O(V + E)`

---

## 3.2 BFS in a Disconnected Graph

The above code only explores one component (from node 0). If the graph is disconnected, we must start BFS from each unvisited vertex.

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> bfsDisconnected(int V, vector<vector<int>> adj) {
        vector<int> bfs;
        vector<int> visited(V, 0);

        for (int start = 0; start < V; start++) {
            if (!visited[start]) {
                queue<int> q;
                visited[start] = 1;
                q.push(start);

                while (!q.empty()) {
                    int node = q.front();
                    q.pop();
                    bfs.push_back(node);

                    for (int it : adj[node]) {
                        if (!visited[it]) {
                            visited[it] = 1;
                            q.push(it);
                        }
                    }
                }
            }
        }
        return bfs;
    }
};
```

**Where to declare the queue?**

- In the above code, the queue is **inside the `if (!visited[i])` block**.
- This means: each new BFS (i.e., each new connected component) gets a **fresh empty queue**.
- Otherwise, if the queue were declared outside, old leftover elements from one BFS could incorrectly mix with the next BFS.

So the queue **must** be declared fresh for every new component.

**Visited Array**

- Declared once outside the loop, so it is **global for the whole graph**.
- Ensures that if a node has already been visited in a previous BFS (i.e., in a previous component), it won’t be re-added to another queue.

### Complexity Analysis

- **Time Complexity:** `O(V + E)` – still the same, as each vertex and edge is processed once.
- **Space Complexity:** `O(V)` – visited array and queue.

---

## 3.3 BFS using Adjacency Matrix

If the graph is stored as an adjacency matrix (`V × V` array), BFS requires checking all possible neighbors for each vertex.

### Code

```cpp
void bfs(int V, vector<vector<int>> adj) {
    vector<int> visited(V, 0);
    vector<int> bfs;
    queue<int> q;

    visited[0] = 1;
    q.push(0);

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        bfs.push_back(node);

        for (int v = 0; v < V; v++) {
            if (adj[node][v] && !visited[v]) {
                visited[v] = 1;
                q.push(v);
            }
        }
    }

    for (int x : bfs) cout << x << " ";
}
```

### Complexity Analysis

- **Time Complexity:** `O(V²)` – because for each vertex we may check all V neighbors.
- **Space Complexity:** `O(V²)` for the adjacency matrix + `O(V)` for visited and queue.

---

THE END
