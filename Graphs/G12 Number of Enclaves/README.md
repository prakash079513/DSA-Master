# Number of Enclaves

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

You are given an `N x M` binary matrix `grid`, where:

- `0` represents **sea**, and
- `1` represents **land**.

A **move** means moving from one land cell to another **4-directionally adjacent** land cell or walking **off the boundary** of the grid.

Your task is to **find the number of land cells from which it is not possible to walk off the boundary**, no matter how many moves you take.

In other words, count all land cells that are **completely enclosed by sea**.

---

## Approach 1 – BFS (Recommended)

### Why BFS?

- We use **BFS** instead of **DFS** in the Number of Enclaves problem mainly for practical and performance reasons.
- Both algorithms work correctly since the goal is just to traverse connected land cells, but BFS avoids deep recursion that can cause stack overflow in large grids.
- BFS uses an explicit queue, making it safer for large input sizes and iterative in nature.
- DFS is often preferred when recursion depth is small or when we want simpler code.

Thus, BFS is the recommended and safer choice for large grids in production.

### Intuition

This is a **boundary-based flood fill problem**, very similar to the _“Replace O’s with X”_ or _“Surrounded Regions”_ problem.

The logic:

- Any land (`1`) connected to the **boundary** is **not enclosed**, because from it, you can walk off the grid.
- The remaining land cells (not connected to boundary land) are **enclaves**.

### Plan

1. Traverse all **boundary cells** (first/last row and first/last column).
2. For every boundary cell that is land (`1`), perform BFS to mark all **reachable lands** as **visited** (or change them to `0` temporarily).
3. After this flood fill, all the land cells connected to the boundary will be marked.
4. Finally, count all remaining cells that are still `1` — these are enclaves.

---

### Code (BFS Approach)

```cpp
void bfs(int r, int c, vector<vector<int>> &grid, vector<vector<int>> &vis, int n, int m) {
    queue<pair<int,int>> q;
    q.push({r, c});
    vis[r][c] = 1;

    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    while (!q.empty()) {
        auto [row, col] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nr = row + dr[i];
            int nc = col + dc[i];
            if (nr >= 0 && nr < n && nc >= 0 && nc < m &&
                !vis[nr][nc] && grid[nr][nc] == 1) {
                vis[nr][nc] = 1;
                q.push({nr, nc});
            }
        }
    }
}

int numEnclaves(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> vis(n, vector<int>(m, 0));

    // Step 1: Flood fill from all boundary land cells
    for (int j = 0; j < m; j++) {
        if (grid[0][j] == 1 && !vis[0][j]) bfs(0, j, grid, vis, n, m);
        if (grid[n-1][j] == 1 && !vis[n-1][j]) bfs(n-1, j, grid, vis, n, m);
    }
    for (int i = 0; i < n; i++) {
        if (grid[i][0] == 1 && !vis[i][0]) bfs(i, 0, grid, vis, n, m);
        if (grid[i][m-1] == 1 && !vis[i][m-1]) bfs(i, m-1, grid, vis, n, m);
    }

    // Step 2: Count remaining unvisited land cells
    int enclaves = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1 && !vis[i][j])
                enclaves++;
        }
    }

    return enclaves;
}
```

---

### Complexity Analysis

**Time Complexity:** `O(N*M)` – Each cell is visited at most once during BFS.

**Space Complexity:** `O(N*M)` – For the visited matrix and queue.

---

## Approach 2 – DFS (Alternative Approach)

### Idea

The logic is exactly the same, but instead of using BFS, we use recursive DFS to mark all boundary-connected lands as visited.

This version is more compact but may risk stack overflow for very large grids.

---

### Code (DFS Approach)

```cpp
void dfs(int r, int c, vector<vector<int>> &grid, vector<vector<int>> &vis, int n, int m) {
    vis[r][c] = 1;

    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr >= 0 && nr < n && nc >= 0 && nc < m &&
            !vis[nr][nc] && grid[nr][nc] == 1) {
            dfs(nr, nc, grid, vis, n, m);
        }
    }
}

int numEnclaves(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> vis(n, vector<int>(m, 0));

    // Step 1: DFS from boundary lands
    for (int j = 0; j < m; j++) {
        if (grid[0][j] == 1 && !vis[0][j]) dfs(0, j, grid, vis, n, m);
        if (grid[n-1][j] == 1 && !vis[n-1][j]) dfs(n-1, j, grid, vis, n, m);
    }
    for (int i = 0; i < n; i++) {
        if (grid[i][0] == 1 && !vis[i][0]) dfs(i, 0, grid, vis, n, m);
        if (grid[i][m-1] == 1 && !vis[i][m-1]) dfs(i, m-1, grid, vis, n, m);
    }

    // Step 2: Count remaining unvisited land cells
    int enclaves = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1 && !vis[i][j])
                enclaves++;
        }
    }

    return enclaves;
}
```

---

### Complexity Analysis

**Time Complexity:** `O(N*M)` – Each land cell is visited once.

**Space Complexity:** `O(N*M)` – For visited array and recursion stack.

---

THE END
