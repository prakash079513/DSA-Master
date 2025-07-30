#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& maze) {
        int m = maze.size(), n = maze[0].size();
        if (maze[0][0] == -1 || maze[m - 1][n - 1] == -1) return 0;
        vector<int> prev(n, 0);
        for (int i = 0; i < m; i++) {
            vector<int> curr(n, 0);
            for (int j = 0; j < n; j++) {
                if (maze[i][j] == -1) {
                    curr[j] = 0;
                } else if (i == 0 && j == 0) {
                    curr[j] = 1;
                } else {
                    int up = (i > 0) ? prev[j] : 0;
                    int left = (j > 0) ? curr[j - 1] : 0;
                    curr[j] = up + left;
                }
            }
            prev = curr;
        }
        return prev[n - 1];
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
