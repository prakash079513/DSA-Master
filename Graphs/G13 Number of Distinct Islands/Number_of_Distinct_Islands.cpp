#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
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
};

int main() {
    vector<vector<int>> grid = {
        {1, 1, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1},
        {0, 0, 0, 1, 0}
    };

    Solution s;
    cout << s.countDistinctIslands(grid);
    return 0;
}