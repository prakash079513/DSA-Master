## **Topological Sort (using DFS)**

Author: [Prakash JC](https://prakash079513.github.io)

### **Where It Is Applied**

- Topological Sorting applies **only to Directed Acyclic Graphs (DAGs)** — graphs with directed edges and **no cycles**.
- It provides a **linear ordering** of vertices such that for every directed edge `(u → v)`, **u appears before v**.
- Common applications:
  - Task scheduling with dependencies.
  - Course prerequisite ordering.
  - Build systems (where some components depend on others).
  - Compilation order of modules.

---

### **Core Idea**

- The key idea is to process nodes **after all their dependencies** (outgoing edges) have been explored.
- This means:
  - We recursively visit all unvisited neighbors of a node.
  - Once all its neighbors are processed, we **push the node into a stack**.
  - Reversing this order (stack top to bottom) gives the topological order.

---

### **Approach**

1. **Maintain a visited array** to track processed nodes.
2. **Perform DFS** for each unvisited node.
3. In DFS:
   - Mark the node as visited.
   - Recursively call DFS on all its unvisited neighbors.
   - After visiting all neighbors, **push the current node into a stack**.
4. After completing all DFS calls, **pop elements from the stack** to get the topological order.

### **Code**

```cpp
void dfs(int node, vector<int> adj[], vector<int>& vis, stack<int>& st) {
    vis[node] = 1;
    for (auto it : adj[node]) {
        if (!vis[it]) dfs(it, adj, vis, st);
    }
    st.push(node);
}

vector<int> topoSort(int V, vector<int> adj[]) {
    vector<int> vis(V, 0);
    stack<int> st;

    for (int i = 0; i < V; i++) {
        if (!vis[i]) dfs(i, adj, vis, st);
    }

    vector<int> topo;
    while (!st.empty()) {
        topo.push_back(st.top());
        st.pop();
    }
    return topo;
}
```

### **Complexity Analysis**

**Time Complexity:** `O(V + E)` – Each node and its edges are visited exactly once.

**Space Complexity:** `O(V)` – For visited array, recursion stack, and final ordering stack.

---

THE END
