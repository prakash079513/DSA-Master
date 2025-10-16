# Number of Islands

Author: [Prakash JC](https://prakash079513.github.io)

## **Problem Statement**

You are given a grid of size `n × m` consisting of 0s and 1s.

A group of 1s that are connected horizontally, vertically, or diagonally forms an **island**.

Your task is to find the total number of such islands.

---

## **Using Depth-First Search (DFS)**

### **Approach**

- Traverse each cell in the grid.
- When a cell with value `1` is found and not yet visited, it indicates the start of a new island.
- Increment the island counter.
- Perform **DFS** from that cell to mark all its connected 1s (in 8 directions) as visited.
  - In dfs: When a call started, mark it as visited, for all neighbors, if not oob and value is 1 and not visited, then mark it as visited.
- This ensures we do not count the same island multiple times.
- Continue scanning until all cells are processed.

### **Code**

```cpp
void dfs(int row, int col, vector<vector<int>> &visited, vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();
    visited[row][col] = 1;

    // Explore 8 directions
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            int rn = row + dr;
            int cn = col + dc;
            if (rn >= 0 && rn < n && cn >= 0 && cn < m &&
                grid[rn][cn] == 1 && !visited[rn][cn]) {
                dfs(rn, cn, visited, grid);
            }
        }
    }
}

int numIslands(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();
    int islands = 0;
    vector<vector<int>> visited(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1 && !visited[i][j]) {
                islands++;
                dfs(i, j, visited, grid);
            }
        }
    }
    return islands;
}
```

### **Complexity Analysis**

**Time Complexity:** `O(n * m)` - Each cell is visited once in DFS traversal.

**Space Complexity:** `O(n * m)` - Due to the visited matrix and recursion stack.

---

## **Using Breadth-First Search (BFS)**

### **Approach**

- Similar idea as DFS, but instead of recursion, use a queue for BFS traversal.
- When a cell with `1` is found and not visited, start a BFS from that cell.
- Push the cell into the queue and mark it visited.
- While the queue is not empty:
  - Pop the front cell and explore all 8 directions.
  - For each valid unvisited neighbor with `1`, push it into the queue.
- Increment the island counter for each BFS initiated.
- Continue until all cells are processed.

### **Code**

```cpp
void bfs(int row, int col, vector<vector<int>> &visited, vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();
    queue<pair<int, int>> q;
    visited[row][col] = 1;
    q.push({row, col});

    while (!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();

        // Explore 8 directions
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                int rn = r + dr;
                int cn = c + dc;
                if (rn >= 0 && rn < n && cn >= 0 && cn < m &&
                    grid[rn][cn] == 1 && !visited[rn][cn]) {
                    visited[rn][cn] = 1;
                    q.push({rn, cn});
                }
            }
        }
    }
}

int numIslands(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();
    int islands = 0;
    vector<vector<int>> visited(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1 && !visited[i][j]) {
                islands++;
                bfs(i, j, visited, grid);
            }
        }
    }
    return islands;
}
```

### **Complexity Analysis**

**Time Complexity:** `O(n * m)` - Each cell is visited once during BFS traversal.

**Space Complexity:** `O(n * m)` - For the visited matrix and BFS queue.

---

THE END
