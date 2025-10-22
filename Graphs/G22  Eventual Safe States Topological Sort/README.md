## **Eventual Safe States Topological Sort**

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

You are given a directed graph with `V` vertices represented as an adjacency list `graph`, where `graph[i]` contains all nodes that node `i` points to.

A node is called **eventually safe** if starting from it, all possible paths lead to terminal nodes (nodes with no outgoing edges). You must return all such safe nodes in sorted order.

---

### Intuition

In the DFS approach, we detect cycles directly using recursion.

In this **BFS Topological Sort (Kahn’s Algorithm)** approach, we work **backwards** — we reverse the graph so that edges point from children to parents.

Now, a **terminal node** (originally with no outgoing edges) becomes a node with **no incoming edges** in the reversed graph.

By performing topological sorting on this reversed graph, we can identify all nodes that are not part of any cycle (i.e., safe nodes).

---

### Approach (Kahn’s Algorithm on Reversed Graph)

1. **Reverse the Graph:**
   - For every edge `u → v` in the original graph, create an edge `v → u` in the reversed graph.
2. **Compute Indegree:**
   - For each node, count how many incoming edges it has in the reversed graph.
3. **Push All Terminal Nodes:**
   - Nodes with `indegree = 0` are terminal nodes (safe).
4. **Perform BFS:**
   - Use a queue for Kahn’s algorithm.
   - Remove nodes from the queue and decrease indegree of all their neighbors.
   - If a neighbor’s indegree becomes 0, it’s also safe — push it into the queue.
5. **Result:**
   - After BFS completes, all nodes visited in this process are safe.
   - Sort and return them.

---

### Code

```cpp
vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
    int V = graph.size();
    vector<vector<int>> revGraph(V);
    vector<int> indegree(V, 0);

    // Reverse the graph
    for (int u = 0; u < V; u++) {
        for (auto v : graph[u]) {
            revGraph[v].push_back(u);
            indegree[u]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    vector<int> safe;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        safe.push_back(node);

        for (auto neigh : revGraph[node]) {
            indegree[neigh]--;
            if (indegree[neigh] == 0) q.push(neigh);
        }
    }

    sort(safe.begin(), safe.end());
    return safe;
}
```

---

### Complexity Analysis

**Time Complexity:** `O(V + E)` – Each vertex and edge is processed once during graph reversal and BFS.

**Space Complexity:** `O(V + E)` – For the reversed graph, indegree array, and queue.

---

THE END
