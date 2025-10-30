# Shortest Distance in a Binary Maze

**Author:** [Prakash JC](https://prakash079513.github.io/)

## Problem Statement

You are given a binary matrix `grid` of size `N x M`, where each cell can either be `0` (blocked) or `1` (open).

You are also given a **source** cell `(srcX, srcY)` and a **destination** cell `(destX, destY)`.

Find the **shortest path distance** from the source to the destination cell such that you can move only in **4 directions** (up, down, left, right), and only through cells with value `1`.

If no such path exists, return `-1`.

---

### Approach

1. **Observation:**

   Since all moves have equal cost (each move = 1 step), this problem is a direct application of **Breadth-First Search (BFS)** — the first time we reach a cell, it’s guaranteed to be the shortest path to that cell.

   Normal queue is sufficient as distances are same and all distances will be stored in increasing fashion.

2. **Steps:**
   - Use a queue to perform BFS from the source cell.
   - Maintain a `dist` matrix initialized with a large value (`1e9`) for all cells.
   - Set `dist[srcX][srcY] = 0` and push `(srcX, srcY, 0)` into the queue.
   - For each step, explore all 4 directions (up, down, left, right).
   - If the next cell is within bounds, not blocked (`1`), and can be reached with a smaller distance, update it and push it to the queue.
   - If we reach the destination, return the distance immediately.
   - If the BFS finishes and destination is not reached, return `1`.

---

### Code

```cpp
int shortestPath(vector<vector<int>> &grid, pair<int,int> source, pair<int,int> destination) {
    int n = grid.size(), m = grid[0].size();
    if (grid[source.first][source.second] == 0 || grid[destination.first][destination.second] == 0)
        return -1;

    vector<vector<int>> dist(n, vector<int>(m, 1e9));
    dist[source.first][source.second] = 0;

    queue<pair<int, pair<int,int>>> q;
    q.push({0, {source.first, source.second}});

    int dRow[] = {-1, 0, 1, 0};
    int dCol[] = {0, 1, 0, -1};

    while (!q.empty()) {
        auto it = q.front();
        q.pop();
        int d = it.first;
        int r = it.second.first;
        int c = it.second.second;

        if (r == destination.first && c == destination.second)
            return d;

        for (int i = 0; i < 4; i++) {
            int nr = r + dRow[i];
            int nc = c + dCol[i];
            if (nr >= 0 && nc >= 0 && nr < n && nc < m && grid[nr][nc] == 1 && d + 1 < dist[nr][nc]) {
                dist[nr][nc] = d + 1;
                q.push({d + 1, {nr, nc}});
            }
        }
    }
    return -1;
}
```

### Complexity Analysis

**Time Complexity:** `O(N * M)` — Each cell is visited at most once.

**Space Complexity:** `O(N * M)` — For the queue and distance matrix.

---

THE END
