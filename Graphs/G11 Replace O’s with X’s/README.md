# **Replace O’s with X’s**

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

You are given a matrix `mat` of size `N x M` containing only `'O'` and `'X'`. You need to replace all `'O'`s that are **completely surrounded** by `'X'`s with `'X'`.

An `'O'` (or group of `'O'`s) is considered **surrounded** if none of its connected `'O'`s (connected 4-directionally) touches the boundary of the matrix.

If an `'O'` is connected to a boundary `'O'`, it **cannot** be surrounded and must remain `'O'`.

---

## Approach – BFS/DFS (Boundary Traversal Approach)

This is a **graph traversal problem** on a 2D grid, and both BFS and DFS can solve it.

The expected and most efficient approach is **DFS** (or equivalently BFS), starting from **boundary 'O's**.

### Intuition

- Any `'O'` on the **boundary** (first/last row or first/last column) **cannot** be converted to `'X'` because it’s not surrounded.
- Also, any `'O'` **connected to these boundary 'O's** cannot be surrounded.
- Therefore:
  1. First, mark all `'O'`s connected to the boundary `'O'`s as **visited**.
  2. Then, convert all remaining `'O'`s that are not visited to `'X'`.

This ensures that only truly surrounded `'O'`s are replaced.

---

## Steps

1. Traverse all **boundary cells** (first and last rows, first and last columns).
2. If a boundary cell is `'O'`, perform DFS/BFS to mark it and all connected `'O'`s as **visited**.
3. After marking:
   - Replace all remaining `'O'`s with `'X'` (they are surrounded).

---

### Code (DFS Approach)

```cpp
void dfs(int r, int c, vector<vector<char>> &mat, vector<vector<int>> &vis, int n, int m) {
    vis[r][c] = 1;

    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr >= 0 && nr < n && nc >= 0 && nc < m && !vis[nr][nc] && mat[nr][nc] == 'O') {
            dfs(nr, nc, mat, vis, n, m);
        }
    }
}

vector<vector<char>> fill(int n, int m, vector<vector<char>> mat) {
    vector<vector<int>> vis(n, vector<int>(m, 0));

    // Step 1: Mark all boundary-connected 'O's as visited
    for (int j = 0; j < m; j++) {
        if (mat[0][j] == 'O' && !vis[0][j]) dfs(0, j, mat, vis, n, m);
        if (mat[n-1][j] == 'O' && !vis[n-1][j]) dfs(n-1, j, mat, vis, n, m);
    }
    for (int i = 0; i < n; i++) {
        if (mat[i][0] == 'O' && !vis[i][0]) dfs(i, 0, mat, vis, n, m);
        if (mat[i][m-1] == 'O' && !vis[i][m-1]) dfs(i, m-1, mat, vis, n, m);
    }

    // Step 2: Convert unvisited 'O's to 'X' and visited 'O's stay as 'O'
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!vis[i][j] && mat[i][j] == 'O')
                mat[i][j] = 'X';
        }
    }

    return mat;
}
```

### Complexity Analysis

**Time Complexity:** `O(N*M)` – Each cell is visited at most once during DFS traversal.

**Space Complexity:** `O(N*M)` – For the visited matrix and recursion stack.

---

## Alternate Approach – BFS

### Idea

The logic is identical, but instead of DFS recursion, we use a queue to mark safe `'O'`s starting from the boundary.

### Code (BFS)

```cpp
vector<vector<char>> fill(int n, int m, vector<vector<char>> mat) {
    vector<vector<int>> vis(n, vector<int>(m, 0));
    queue<pair<int, int>> q;

    // Push all boundary 'O's into the queue
    for (int j = 0; j < m; j++) {
        if (mat[0][j] == 'O') { q.push({0, j}); vis[0][j] = 1; }
        if (mat[n-1][j] == 'O') { q.push({n-1, j}); vis[n-1][j] = 1; }
    }
    for (int i = 0; i < n; i++) {
        if (mat[i][0] == 'O') { q.push({i, 0}); vis[i][0] = 1; }
        if (mat[i][m-1] == 'O') { q.push({i, m-1}); vis[i][m-1] = 1; }
    }

    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr >= 0 && nr < n && nc >= 0 && nc < m && !vis[nr][nc] && mat[nr][nc] == 'O') {
                vis[nr][nc] = 1;
                q.push({nr, nc});
            }
        }
    }

    // Replace unvisited 'O's
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!vis[i][j] && mat[i][j] == 'O')
                mat[i][j] = 'X';
        }
    }

    return mat;
}
```

### Complexity Analysis

**Time Complexity:** `O(N*M)` – Every cell is processed at most once.

**Space Complexity:** `O(N*M)` – For the visited matrix and queue.

---

END
