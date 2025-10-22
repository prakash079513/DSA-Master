## **Detect Cycle in a Directed Graph using Kahn’s Algorithm**

Author: [Prakash JC](https://prakash079513.github.io)

### **Intuition**

- In a **Directed Acyclic Graph (DAG)**, **Topological Sorting** is possible because there exists at least one node with **in-degree 0** at every step.
- However, if a graph contains a **cycle**, no node within that cycle will ever reach in-degree 0 (since they depend on each other).
- Hence, when applying **Kahn’s Algorithm**, if we cannot process all vertices (i.e., topological sort count < V), it means there is a **cycle** in the graph.

---

### **Approach**

1. Compute the **in-degree** for every vertex.
2. Push all vertices with **in-degree 0** into a queue.
3. Initialize a counter `count = 0` to track how many nodes are processed.
4. While the queue is not empty:
   - Pop a node and increment `count`.
   - For each neighbor, decrease its in-degree by 1.
   - If a neighbor’s in-degree becomes 0, push it into the queue.
5. After processing all nodes, check if `count == V`:
   - If true, **no cycle** exists (graph is a DAG).
   - If false, **a cycle** exists (some nodes never reached in-degree 0).

---

### **Code**

```cpp
bool isCyclic(int V, vector<int> adj[]) {
    vector<int> indegree(V, 0);

    for (int i = 0; i < V; i++) {
        for (auto it : adj[i]) {
            indegree[it]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    int count = 0;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        count++;

        for (auto it : adj[node]) {
            indegree[it]--;
            if (indegree[it] == 0) q.push(it);
        }
    }

    // If count != V, graph has a cycle
    return count != V;
}
```

---

### **Complexity Analysis**

**Time Complexity:** `O(V + E)` – Every vertex and edge is processed once during BFS traversal.

**Space Complexity:** `O(V)` – For the in-degree array, queue, and bookkeeping.

---

THE END
