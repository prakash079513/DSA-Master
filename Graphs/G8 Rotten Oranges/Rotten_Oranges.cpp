#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int orangesRotting(vector<vector<int>> &grid) {
        int n = grid.size();
        int m = grid[0].size();

        queue<pair<pair<int, int>, int>> q; // ((row, col), time)
        int freshCount = 0;

        // Step 1: Push all initially rotten oranges into queue
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 2) {
                    q.push({{i, j}, 0});
                } else if (grid[i][j] == 1) {
                    freshCount++;
                }
            }
        }

        int time = 0;
        int delRow[] = {-1, 0, 1, 0};
        int delCol[] = {0, 1, 0, -1};
        int rottenCount = 0;

        // Step 2: Perform BFS
        while (!q.empty()) {
            int r = q.front().first.first;
            int c = q.front().first.second;
            int t = q.front().second;
            q.pop();

            time = max(time, t);

            for (int i = 0; i < 4; i++) {
                int rn = r + delRow[i];
                int cn = c + delCol[i];

                if (rn >= 0 && rn < n && cn >= 0 && cn < m && grid[rn][cn] == 1) {
                    grid[rn][cn] = 2;
                    rottenCount++;
                    q.push({{rn, cn}, t + 1});
                }
            }
        }

        // Step 3: Check if all fresh oranges became rotten
        if (rottenCount != freshCount) return -1;
        return time;
    }
};

int main() {
    vector<vector<int>> grid = {
        {2, 1, 1},
        {0, 1, 1},
        {1, 0, 1}
    };
    Solution s1;
    cout << s1.orangesRotting(grid);
    return 0;
}