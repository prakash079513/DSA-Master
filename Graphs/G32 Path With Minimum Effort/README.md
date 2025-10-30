## Path With Minimum Effort

**Author:** [Prakash JC](https://prakash079513.github.io)

---

### Problem Statement

You are given a 2D grid `heights` where `heights[i][j]` denotes the height of a cell.
You start at the **top-left cell (0, 0)** and need to reach the **bottom-right cell (rows-1, cols-1)** by moving in **4 directions** (up, down, left, right).

The **effort** of a path is defined as the **maximum absolute difference** in heights between two consecutive cells in the path.

Your goal is to find the **minimum possible effort** required to reach the destination.

If multiple paths exist, choose the one with the smallest effort.

---

### Approach

1. **Observation:**

   - This is **not** a simple BFS because every edge (move) has a different cost (difference in heights).
   - Hence, we use **Dijkstra’s Algorithm** to find the minimum “maximum edge cost” path.

2. **How it works:**

   - Maintain a `dist` matrix that stores the minimum effort needed to reach each cell.
   - Initialize all distances to infinity (`1e9`), except for `(0,0)` = 0.
   - Use a **min-heap (priority_queue)** that stores `{effort, {r, c}}`.
   - Pop the cell with the minimum current effort.
   - For each of its 4 neighbors:

     - Compute the new effort as `max(currentEffort, abs(heights[nr][nc] - heights[r][c]))`.
     - If this new effort is smaller than the stored distance, update and push to the heap.

   - Once we pop the destination cell, we can return its effort (as Dijkstra ensures minimality).

3. **Why Priority Queue:**

   - Because we need to always expand the node (cell) with the **smallest current effort**, ensuring the first time we reach the destination is the minimal one.

---

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int n = heights.size(), m = heights[0].size();
        vector<vector<int>> dist(n, vector<int>(m, 1e9));
        dist[0][0] = 0;

        priority_queue<
            pair<int, pair<int,int>>,
            vector<pair<int, pair<int,int>>>,
            greater<pair<int, pair<int,int>>>
        > pq;

        pq.push({0, {0, 0}});

        int dRow[] = {-1, 0, 1, 0};
        int dCol[] = {0, 1, 0, -1};

        while (!pq.empty()) {
            auto it = pq.top();
            pq.pop();
            int diff = it.first;
            int r = it.second.first;
            int c = it.second.second;

            if (r == n - 1 && c == m - 1)
                return diff;

            for (int i = 0; i < 4; i++) {
                int nr = r + dRow[i];
                int nc = c + dCol[i];

                if (nr >= 0 && nc >= 0 && nr < n && nc < m) {
                    int newEffort = max(diff, abs(heights[nr][nc] - heights[r][c]));
                    if (newEffort < dist[nr][nc]) {
                        dist[nr][nc] = newEffort;
                        pq.push({newEffort, {nr, nc}});
                    }
                }
            }
        }
        return 0; // unreachable
    }
};

int main() {
    vector<vector<int>> heights = {{1,2,2},{3,8,2},{5,3,5}};
    Solution s;
    cout << s.minimumEffortPath(heights);
    return 0;
}
```

---

### Complexity Analysis

**Time Complexity:** `O(N*M * log(N*M))` — Each cell may be pushed into the priority queue once, and heap operations cost `log(N*M)`.
**Space Complexity:** `O(N*M)` — For the distance matrix and priority queue storage.

---

This approach ensures we always find the path with the **minimum possible maximum effort**, efficiently using Dijkstra’s algorithm for variable edge costs.
