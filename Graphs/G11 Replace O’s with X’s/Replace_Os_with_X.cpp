#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
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

        // Step 1: Mark all boundary-connected 'O's as safe
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
};

int main() {
    vector<vector<char>> mat = {
        {'X', 'X', 'X', 'X'},
        {'X', 'O', 'X', 'X'},
        {'X', 'O', 'O', 'X'},
        {'X', 'O', 'X', 'X'},
        {'X', 'X', 'O', 'O'}
    };
    int n = mat.size(), m = mat[0].size();
    Solution s;
    vector<vector<char>> res = s.fill(n, m, mat);

    for (auto &row : res) {
        for (char ch : row) cout << ch << " ";
        cout << endl;
    }
    return 0;
}