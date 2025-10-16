# Number of Distinct Islands

Author: [Prakash JC](https://prakash079513.github.io)

---

## Problem Statement

Given a binary grid of size `N x M` where `0` represents water and `1` represents land, find the number of **distinct** islands.

Two islands are considered **distinct** if their **shapes** (relative positions of land cells) are different, regardless of where they appear in the grid.

---

## Recommended Approach: **Depth First Search (DFS)**

### Approach

Unlike the simple island-count problem, here we must **identify unique island shapes**.

The idea:

1. Traverse the grid.
2. When an unvisited land cell (`1`) is found, start a **DFS** from that cell.
3. Record the **relative coordinates** of each land cell in the current island with respect to the starting cell (base cell).
   - Example: if DFS starts at `(baseRow, baseCol)`, and you visit `(r, c)`, record `(r - baseRow, c - baseCol)`.
4. Once the DFS for an island is complete, store the vector of relative coordinates as its shape.
5. Use a `set` of vectors to automatically filter out duplicate shapes.
6. The final size of this set gives the number of distinct islands.

This method ensures that two islands with the same shape but different positions are treated as one.

### Code (DFS)

```cpp
void dfs(int r, int c, vector<vector<int>>& grid, vector<vector<int>>& vis,
            vector<pair<int, int>>& shape, int baseR, int baseC) {
    int n = grid.size();
    int m = grid[0].size();
    vis[r][c] = 1;
    shape.push_back({r - baseR, c - baseC});

    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    for (int k = 0; k < 4; k++) {
        int nr = r + dr[k];
        int nc = c + dc[k];
        if (nr >= 0 && nr < n && nc >= 0 && nc < m &&
            !vis[nr][nc] && grid[nr][nc] == 1) {
            dfs(nr, nc, grid, vis, shape, baseR, baseC);
        }
    }
}

int countDistinctIslands(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> vis(n, vector<int>(m, 0));
    set<vector<pair<int, int>>> shapes;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!vis[i][j] && grid[i][j] == 1) {
                vector<pair<int, int>> shape;
                dfs(i, j, grid, vis, shape, i, j);
                shapes.insert(shape);
            }
        }
    }
    return shapes.size();
}
```

### Complexity Analysis

**Time Complexity:** `O(N*M)` – Each cell is visited once in DFS traversal.

**Space Complexity:** `O(N*M)` – For visited matrix, recursion stack, and storing shapes.

---

## Alternative Approach: **Breadth First Search (BFS)**

### Approach

We can replace DFS with BFS:

1. When a new land cell is found, start BFS and record relative positions.
2. Store the relative shape of each island.
3. Use a set to count distinct shapes.

This avoids recursion stack limits and is better suited for very large grids.

### Code (BFS)

```cpp
int countDistinctIslands(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> vis(n, vector<int>(m, 0));
    set<vector<pair<int, int>>> shapes;
    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!vis[i][j] && grid[i][j] == 1) {
                vector<pair<int, int>> shape;
                queue<pair<int, int>> q;
                q.push({i, j});
                vis[i][j] = 1;
                int baseR = i, baseC = j;

                while (!q.empty()) {
                    auto [r, c] = q.front();
                    q.pop();
                    shape.push_back({r - baseR, c - baseC});

                    for (int k = 0; k < 4; k++) {
                        int nr = r + dr[k];
                        int nc = c + dc[k];
                        if (nr >= 0 && nr < n && nc >= 0 && nc < m &&
                            !vis[nr][nc] && grid[nr][nc] == 1) {
                            vis[nr][nc] = 1;
                            q.push({nr, nc});
                        }
                    }
                }
                shapes.insert(shape);
            }
        }
    }
    return shapes.size();
```

### Complexity Analysis

**Time Complexity:** `O(N*M)` – Every cell is processed once in BFS.

**Space Complexity:** `O(N*M)` – For queue, visited matrix, and shape storage.

---

THE END
