#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
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
};

int main() {
    vector<vector<int>> grid = {
        {0, 0, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    };
    Solution s;
    cout << s.numEnclaves(grid);
    return 0;
}