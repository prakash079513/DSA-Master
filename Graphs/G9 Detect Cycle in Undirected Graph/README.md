# **Detect Cycle in an Undirected Graph**

Author: [Prakash JC](https://prakash079513.github.io)

## **Problem Statement**

You are given an **undirected graph** with `V` vertices and `E` edges.

Your task is to determine **whether the graph contains any cycle or not**.

If there exists a path such that you start from a node and can return to it by traversing edges (without reusing any edge in the same direction), the graph contains a **cycle**.

---

## **Breadth-First Search (BFS) — Recommended**

### **Why BFS is Recommended**

- BFS explores nodes level by level, maintaining a **parent** relationship for each node.
- This helps us identify a cycle efficiently when we encounter an already visited node that is **not the parent** of the current node.
- BFS avoids deep recursion and is usually more stable for large graphs.

---

### **Approach**

- Use a **visited array** of size `V` initialized to 0.
- For each unvisited node, perform BFS:
  - Push the node into a queue as `(node, parent)`, where `parent = -1` for the start.
  - While the queue is not empty:
    - Pop `(node, parent)` from the queue.
    - For each adjacent neighbor:
      - If the neighbor is **unvisited**, mark it visited and push `(neighbor, node)` into the queue.
      - If the neighbor is **already visited** and **not the parent**, it indicates a **cycle**.
- If any component’s BFS detects a cycle, return `true`.
- If no cycles are found after traversing all components, return `false`.

---

### **Code**

```cpp
bool checkForCycle(int src, vector<int> adj[], vector<int> &visited) {
    queue<pair<int, int>> q; // {node, parent}
    visited[src] = 1;
    q.push({src, -1});

    while (!q.empty()) {
        int node = q.front().first;
        int parent = q.front().second;
        q.pop();

        for (auto neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = 1;
                q.push({neighbor, node});
            }
            // If already visited and not parent → cycle
            else if (neighbor != parent) {
                return true;
            }
        }
    }
    return false;
}

bool isCycle(int V, vector<int> adj[]) {
    vector<int> visited(V, 0);

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (checkForCycle(i, adj, visited)) return true;
        }
    }
    return false;
}
```

### **Complexity Analysis**

**Time Complexity:** `O(V + E)` — Each vertex and edge is processed once in BFS traversal.

**Space Complexity:** `O(V)` — For the visited array and queue.

---

## **Depth-First Search (DFS)**

### **Approach**

- Use recursion to perform DFS traversal.
- Maintain a **visited array**.
- For each unvisited node, start a DFS with a `parent` parameter:
  - Mark the current node as visited.
  - For each neighbor:
    - If the neighbor is not visited, recursively DFS with the current node as parent.
    - If the neighbor is **visited** and **not the parent**, a **cycle exists**.
- If DFS detects a cycle in any component, return `true`.

---

### **Code**

```cpp
bool dfs(int node, int parent, vector<int> adj[], vector<int> &visited) {
    visited[node] = 1;

    for (auto neighbor : adj[node]) {
        if (!visited[neighbor]) {
            if (dfs(neighbor, node, adj, visited)) return true;
        }
        else if (neighbor != parent) {
            return true;
        }
    }
    return false;
}

bool isCycle(int V, vector<int> adj[]) {
    vector<int> visited(V, 0);

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (dfs(i, -1, adj, visited)) return true;
        }
    }
    return false;
}
```

### **Complexity Analysis**

**Time Complexity:** `O(V + E)` — Each vertex and edge is traversed once in DFS recursion.

**Space Complexity:** `O(V)` — For recursion stack and visited array.

---

THE END
