#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int f(int i, int j, vector<vector<int>>& maze, vector<vector<int>>& dp) {
        if (i < 0 || j < 0) return 0;
        if (maze[i][j] == -1) return 0;
        if (i == 0 && j == 0) return 1;
        if (dp[i][j] != -1) return dp[i][j];
        return dp[i][j] = f(i - 1, j, maze, dp) + f(i, j - 1, maze, dp);
    }

    int uniquePathsWithObstacles(vector<vector<int>>& maze) {
        int m = maze.size(), n = maze[0].size();
        if (maze[0][0] == -1 || maze[m - 1][n - 1] == -1) return 0;
        vector<vector<int>> dp(m, vector<int>(n, -1));
        return f(m - 1, n - 1, maze, dp);
    }
};

int main() {
    vector<vector<int>> maze = {
        {0, 0, 0},
        {0, -1, 0},
        {0, 0, 0}
    };
    Solution s1;
    cout << s1.uniquePathsWithObstacles(maze);
    return 0;
}
