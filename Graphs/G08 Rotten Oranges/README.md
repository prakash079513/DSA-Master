# Rotten Oranges

Author: [Prakash JC](https://prakash079513.github.io)

## **Problem Statement**

You are given an `m x n` grid representing oranges:

- `2` → Rotten orange
- `1` → Fresh orange
- `0` → Empty cell

Every minute, any fresh orange that is **4-directionally adjacent** (up, down, left, right) to a rotten orange becomes rotten.

You must find the **minimum number of minutes** that must elapse until **no fresh orange remains**.

If it is **impossible** for all oranges to rot, return `-1`.

---

## **Approach Recommended: Breadth-First Search (BFS)**

**Why BFS and not DFS?**

- BFS processes nodes level by level, which naturally simulates the “minute-by-minute” spread of rotting.
- DFS explores deeply before spreading to other directions, which doesn’t correctly represent simultaneous rotting across all directions.
  Hence, BFS is the correct approach for **multi-source shortest propagation** problems like this.

---

### **Idea**

- Treat each rotten orange as a starting point for BFS (multi-source BFS).
- Each minute corresponds to one BFS level.
- Every time a fresh orange is adjacent to a rotten one, it becomes rotten and is added to the queue for the next level (next minute).
- Keep track of time and count of fresh oranges.
- If, after the BFS traversal, there are still fresh oranges left → return `-1`.

---

### **Step-by-Step Algorithm**

1. Create a queue to store coordinates of **all rotten oranges** and **time** (initially).
2. Push all initially rotten oranges into queue and in the same loop count the number of **fresh oranges**.
3. Initialize required variables. To check whether all are rotten or not, we will have another variable called **rotteCount**.
4. While q is not empty:
   - Take out the front value.
   - Update the answer variable(time).
   - For each, check its 4-directional neighbors.
   - If a neighbor not oob and is a **fresh orange (1)**:
     - Turn it **rotten (2)**.
     - Decrease the count of fresh oranges.
     - Push it into the queue for the next minute.
5. if rotten count is not equal to fresh count `return -1`.
   - Otherwise, return the total time taken.

---

### **Code**

```cpp
int orangesRotting(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();

    queue<pair<pair<int, int>, int>> q; // ((row, col), time)
    int freshCount = 0;

    // Step 1: Push all initially rotten oranges into queue
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 2) {
                q.push({{i, j}, 0});
            } else if (grid[i][j] == 1) {
                freshCount++;
            }
        }
    }

    int time = 0;
    int delRow[] = {-1, 0, 1, 0};
    int delCol[] = {0, 1, 0, -1};
    int rottenCount = 0;

    // Step 2: Perform BFS
    while (!q.empty()) {
        int r = q.front().first.first;
        int c = q.front().first.second;
        int t = q.front().second;
        q.pop();

        time = max(time, t);

        for (int i = 0; i < 4; i++) {
            int rn = r + delRow[i];
            int cn = c + delCol[i];

            if (rn >= 0 && rn < n && cn >= 0 && cn < m && grid[rn][cn] == 1) {
                grid[rn][cn] = 2;
                rottenCount++;
                q.push({{rn, cn}, t + 1});
            }
        }
    }

    // Step 3: Check if all fresh oranges became rotten
    if (rottenCount != freshCount) return -1;
    return time;
}
```

---

### **Complexity Analysis**

**Time Complexity:** `O(n * m)`

- Each cell is visited at most once, and each neighbor check is constant.

**Space Complexity:** `O(n * m)`

- Due to the BFS queue storing coordinates of rotten oranges.

---

THE END
