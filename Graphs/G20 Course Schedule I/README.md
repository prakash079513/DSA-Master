## **Course Schedule I**

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

There are a total of `numCourses` courses you have to take, labeled from `0` to `numCourses - 1`. You are given an array `prerequisites` where `prerequisites[i] = [ai, bi]` indicates that you must take course `bi` first if you want to take course `ai`.

For example, the pair `[0, 1]` indicates that to take course `0` you have to first take course `1`.

Return `true` if you can finish all courses. Otherwise, return `false`.

---

**Example 1:**

Input: `numCourses = 2, prerequisites = [[1,0]]`

Output: `true`

Explanation: There are a total of 2 courses to take.

To take course 1 you should have finished course 0. So it is possible.

---

**Example 2:**

Input: `numCourses = 2, prerequisites = [[1,0],[0,1]]`

Output: `false`

Explanation: There are a total of 2 courses to take.

To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.

## **Approach**

- The problem is equivalent to **detecting a cycle in a directed graph**.
- Each course is a node, and a prerequisite pair `[a, b]` means there is a **directed edge b → a** (to take `a`, you must first take `b`).
- If a **cycle** exists, it means some courses depend on each other, making it **impossible to finish all courses**.
- Therefore, we can use **Kahn’s Algorithm (BFS Topological Sort)**:
  1. Build an adjacency list from the prerequisites.
  2. Compute the **in-degree** of each node (how many prerequisites it has).
  3. Push all nodes with **in-degree 0** (no prerequisites) into a queue.
  4. Repeatedly pop from the queue, decrement in-degrees of dependent nodes, and push any that reach in-degree 0.
  5. Count how many courses are processed; if count equals the total number of courses, all can be finished. Otherwise, a cycle exists.

### **Code**

```cpp
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<int> adj[numCourses];
    vector<int> indegree(numCourses, 0);

    // Build adjacency list and indegree array
    for (auto it : prerequisites) {
        adj[it[1]].push_back(it[0]);
        indegree[it[0]]++;
    }

    queue<int> q;
    // Push courses with no prerequisites
    for (int i = 0; i < numCourses; i++) {
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

    return count == numCourses;
}
```

### **Complexity Analysis**

**Time Complexity:** `O(V + E)` – Each course and prerequisite edge is processed once.

**Space Complexity:** `O(V + E)` – For the adjacency list, in-degree array, and queue.

---

THE END
