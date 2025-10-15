#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
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
};

int main() {
    vector<vector<int>> grid = {{0, 1, 1}, {1, 0, 0}, {0, 0, 1}};
    Solution s;
    vector<vector<int>> ans = s.nearest(grid);

    for (auto &row : ans) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }
    return 0;
}