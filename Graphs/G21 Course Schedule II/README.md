## **Course Schedule II**

Author: [Prakash JC](https://prakash079513.github.io)

### Problem Statement

There are a total of `numCourses` courses you have to take, labeled from `0` to `numCourses - 1`. You are given an array `prerequisites` where `prerequisites[i] = [ai, bi]` indicates that you must take course `bi` first if you want to take course `ai`.

For example, the pair `[0, 1]` indicates that to take course `0` you have to first take course `1`.

Return the **ordering of courses** you should take to finish all courses. If there are many valid answers, return any of them. If it is impossible to finish all courses, return an empty array.

---

**Example 1:**

Input: `numCourses = 2, prerequisites = [[1,0]]`

Output: `[0,1]`

Explanation: There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is `[0,1]`.

---

**Example 2:**

Input: `numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]`

Output: `[0,2,1,3]`

Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2.

Both courses 1 and 2 should be taken after you finished course 0.

So one correct course order is `[0,1,2,3]`. Another correct ordering is `[0,2,1,3]`.

---

## Approach (Kahn’s Algorithm – BFS Topological Sort)

- This is a **topological sorting** problem where we must find a valid order of course completion based on prerequisites.
- A valid topological order exists **only if the graph has no cycle**.
- Construct an **adjacency list** for all edges `b → a` meaning “to take `a`, you must take `b` first”.
- Maintain an **indegree array**, where `indegree[i]` represents how many prerequisites course `i` has.
- Push all courses with `indegree = 0` (no prerequisites) into a queue — they can be taken first.
- Perform BFS:
  - Pop a course from the queue, add it to the final ordering.
  - For each dependent course, reduce its indegree by 1.
  - If any course’s indegree becomes 0, push it into the queue.
- At the end:
  - If the number of courses in the result equals `numCourses`, return the order.
  - Otherwise, a cycle exists — return an empty array.

---

### Code

```cpp
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> adj(numCourses);
    vector<int> indegree(numCourses, 0);

    // Build adjacency list and indegree array
    for (auto& pre : prerequisites) {
        adj[pre[1]].push_back(pre[0]); // this is important
        indegree[pre[0]]++;
    }

    queue<int> q;
    for (int i = 0; i < numCourses; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    vector<int> topo;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        topo.push_back(node);

        for (auto& neighbor : adj[node]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) q.push(neighbor);
        }
    }

    if (topo.size() == numCourses) return topo;
    return {};
}
```

---

### Complexity Analysis

**Time Complexity:** `O(V + E)` – Each node and edge is processed once during BFS.

**Space Complexity:** `O(V + E)` – For storing the adjacency list, indegree array, and queue.

---

THE END
