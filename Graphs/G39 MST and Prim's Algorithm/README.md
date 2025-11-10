# Minimum Spanning Tree, Prim’s Algorithm

**Author:** [Prakash JC](https://prakash079513.github.io/)

A **Minimum Spanning Tree (MST)** of a connected, undirected, and weighted graph is a subset of edges that connects all vertices **without cycles** and with the **minimum possible total edge weight**.

### Key Points:

- MST ensures all nodes are connected with minimal cost.
- It is widely used in **network design**, **clustering**, and **approximation algorithms**.
- Two popular algorithms to find MST:
  - **Prim’s Algorithm**
  - **Kruskal’s Algorithm**

---

### Example

Consider the following weighted graph:

| Edge | Weight |
| ---- | ------ |
| 0–1  | 2      |
| 0–2  | 4      |
| 1–2  | 1      |
| 1–3  | 7      |
| 2–3  | 3      |

The MST will include edges with total weight = **6** (Edges: 1–2, 2–3, 0–1).

---

## Prim’s Algorithm

### Intuition

- Build the MST **incrementally**, starting from any node.
- At each step, choose the **smallest weight edge** that connects a vertex inside the MST to a vertex outside it.
- Repeat until all vertices are included.
- Works efficiently with **priority queue (min-heap)** to always pick the smallest edge.

---

### Approach

1. **Initialize**
   - Create an adjacency list of the graph.
   - Maintain a **min-heap** (priority queue) storing pairs `{weight, node}`.
   - Track visited nodes to avoid cycles.
2. **Start from any node (say node 0)**
   - Push `{0, 0}` into the heap (edge weight 0 for start).
   - Initialize `sum = 0` to store MST weight.
3. **Process heap**
   - Pop the smallest edge from the heap.
   - If already visited, skip.
   - Otherwise, mark as visited and add edge weight to `sum`.
   - Push all adjacent unvisited nodes with their weights into the heap.
4. **Continue until all nodes are visited**
   - The sum of all chosen edges gives the **total weight of MST**.

---

### Code

```cpp
    int spanningTree(int n, vector<vector<int>> adj[]) {
        vector<int> vis(n, 0);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        pq.push({0, 0}); // {weight, node}
        int sum = 0;

        while (!pq.empty()) {
            auto [wt, node] = pq.top();
            pq.pop();

            if (vis[node]) continue;
            vis[node] = 1;
            sum += wt;

            for (auto &edge : adj[node]) {
                int adjNode = edge[0], edgeWt = edge[1];
                if (!vis[adjNode]) pq.push({edgeWt, adjNode});
            }
        }
        return sum;
    }
```

---

### Complexity Analysis

**Time Complexity:** `O(E log V)` – Each edge insertion/extraction from the priority queue takes log(V) time.

- While loop runs for at most all edges i.e., E and every time we need the top value so it is logE.
- And checking the neighbors will be at most E and pushing them into pq is logE.
- So E*logE + E*logE approx as E\*logE

**Space Complexity:** `O(V + E)` – For adjacency list, visited array, and priority queue.

---

THE END
