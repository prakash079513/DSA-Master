#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
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
};

int main() {
    vector<vector<int>> grid = {
        {1, 1, 0, 0, 0},
        {0, 1, 0, 0, 1},
        {1, 0, 0, 1, 1},
        {0, 0, 0, 0, 0},
        {1, 0, 1, 0, 1}
    };
    Solution s1;
    cout << s1.numIslands(grid);
    return 0;
}
