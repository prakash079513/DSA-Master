## **Kahn’s Algorithm (BFS Topo Sort)**

Author: [Prakash JC](https://prakash079513.github.io)

### **Intuition**

- In a directed acyclic graph (DAG), a node can appear before its dependents only if **all its prerequisites (incoming edges)** are already processed.
- Nodes with **no incoming edges (in-degree 0)** are **independent** — they can be placed first in the topological order.
- Once we include such nodes in the order, we remove their outgoing edges, which may make other nodes independent.
- By repeatedly processing nodes with in-degree 0, we build a valid topological ordering.

---

### **Approach**

1. Compute the **in-degree** for each node (number of edges coming into it).
2. Push all nodes with **in-degree 0** into a queue — they have no dependencies.
3. While the queue is not empty:
   - Pop a node from the queue and add it to the topological order.
   - For each of its neighbors, reduce their in-degree by 1.
   - If any neighbor’s in-degree becomes 0, push it into the queue.
4. Continue until all nodes are processed or no 0 in-degree nodes remain.
5. If the number of processed nodes is less than V, the graph contains a cycle.

---

### **Code**

```cpp
vector<int> topoSort(int V, vector<int> adj[]) {
    vector<int> indegree(V, 0);

    // Step 1: Compute indegree of each node
    for (int i = 0; i < V; i++) {
        for (auto it : adj[i]) {
            indegree[it]++;
        }
    }

    // Step 2: Push all nodes with indegree 0 into the queue
    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    // Step 3: Process queue using BFS
    vector<int> topo;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        topo.push_back(node);

        // Step 4: Reduce indegree of neighbors
        for (auto it : adj[node]) {
            indegree[it]--;
            if (indegree[it] == 0) q.push(it);
        }
    }

    return topo;
}
```

---

### **Complexity Analysis**

**Time Complexity:** `O(V + E)` – Each node and edge is processed exactly once during the traversal.

**Space Complexity:** `O(V)` – For the in-degree array, queue, and result list.

---

THE END
