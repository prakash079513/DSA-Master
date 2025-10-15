# **Nearest 1 in Binary Grid**

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

You are given a binary grid of size `N x M`. Each cell contains either `0` or `1`.

For every cell `(i, j)`, find the distance to its **nearest 1**.

Distance between two cells `(i1, j1)` and `(i2, j2)` is defined as

`|i1 - i2| + |j1 - j2|` (Manhattan distance).

---

## Recommended Approach — **BFS (Multi-source BFS)**

### Intuition

BFS is the best approach here because:

- We want the **shortest distance** from each cell to the nearest `1`.
- BFS is ideal for finding the shortest distance in **unweighted grids**.

The idea:

- Treat **all cells with 1** as **sources** (since distance from 1 to itself is 0).
- Start BFS from all these `1`s **simultaneously**.
- Each time we visit a `0`, we assign its distance as `current distance + 1`.
- By doing this level by level, the first time a `0` is reached will be its minimum distance.

---

### Step-by-Step Approach

1. Create a queue `q`.
2. Initialize a `dist` matrix of size `N x M` with `1` or `INT_MAX`.
3. Traverse the grid:
   - If the cell is `1`, push `(i, j)` into the queue and mark `dist[i][j] = 0`.
4. Perform BFS:
   - Pop the front cell `(r, c)` from the queue.
   - For each of its 4 directions `(up, down, left, right)`, if the new cell `(nr, nc)` is inside the grid and not visited:
     - Set `dist[nr][nc] = dist[r][c] + 1`
     - Push `(nr, nc)` into the queue.
5. Return the `dist` matrix.

### Code

```cpp
vector<vector<int>> nearest(vector<vector<int>> grid) {
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> dist(n, vector<int>(m, -1));
    queue<pair<int, int>> q;

    // Step 1: Push all cells with 1
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1) {
                dist[i][j] = 0;
                q.push({i, j});
            }
        }
    }

    // Directions for up, right, down, left
    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    // Step 2: BFS
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr >= 0 && nr < n && nc >= 0 && nc < m && dist[nr][nc] == -1) {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }

    return dist;
}
```

### Complexity Analysis

**Time Complexity:** `O(N*M)` – each cell is visited at most once.

**Space Complexity:** `O(N*M)` – for the queue and distance matrix.

---

## Alternate Approach — **DFS**

### Intuition

DFS can also compute distances, but it's **not efficient** here because:

- It explores **deep paths** first rather than **shortest paths**.
- You may revisit many cells multiple times.
- Needs recursion stack and pruning to avoid overcounting.

Still, it can be done by:

- Running DFS from every cell having 1, updating distances recursively for neighboring 0s.
- Taking the **minimum distance** each time you find a shorter path.

### Code

```cpp
void dfs(int r, int c, int dist, vector<vector<int>> &grid, vector<vector<int>> &ans) {
    int n = grid.size(), m = grid[0].size();
    if (r < 0 || r >= n || c < 0 || c >= m) return;
    if (dist >= ans[r][c]) return; // already a shorter distance found

    ans[r][c] = dist;
    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    for (int i = 0; i < 4; i++)
        dfs(r + dr[i], c + dc[i], dist + 1, grid, ans);
}

vector<vector<int>> nearest(vector<vector<int>> grid) {
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> ans(n, vector<int>(m, INT_MAX));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1)
                dfs(i, j, 0, grid, ans);
        }
    }

    return ans;
}
```

### Complexity Analysis

**Time Complexity:** `O((N*M)²)` – since each DFS can visit many cells repeatedly.

**Space Complexity:** `O(N*M)` – recursion stack + distance matrix.

---

THE END
