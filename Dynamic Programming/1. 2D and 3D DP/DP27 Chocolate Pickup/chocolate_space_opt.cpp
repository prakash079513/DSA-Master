#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumChocolates(int m, int n, vector<vector<int>>& grid) {
        vector<vector<int>> front(n, vector<int>(n, 0)), curr(n, vector<int>(n, 0));

        // Base case for the last row
        for (int j1 = 0; j1 < n; j1++) {
            for (int j2 = 0; j2 < n; j2++) {
                if (j1 == j2)
                    front[j1][j2] = grid[m - 1][j1];
                else
                    front[j1][j2] = grid[m - 1][j1] + grid[m - 1][j2];
            }
        }

        for (int i = m - 2; i >= 0; i--) {
            for (int j1 = 0; j1 < n; j1++) {
                for (int j2 = 0; j2 < n; j2++) {
                    int maxi = INT_MIN;

                    for (int dj1 = -1; dj1 <= 1; dj1++) {
                        for (int dj2 = -1; dj2 <= 1; dj2++) {
                            int nj1 = j1 + dj1;
                            int nj2 = j2 + dj2;

                            if (nj1 >= 0 && nj1 < n && nj2 >= 0 && nj2 < n) {
                                int value = 0;
                                if (j1 == j2)
                                    value = grid[i][j1];
                                else
                                    value = grid[i][j1] + grid[i][j2];

                                value += front[nj1][nj2];
                                maxi = max(maxi, value);
                            }
                        }
                    }

                    curr[j1][j2] = maxi;
                }
            }
            front = curr;
        }

        return front[0][n - 1];
    }
};

int main() {
    int m = 4, n = 3;
    vector<vector<int>> grid = {
        {2, 3, 1},
        {3, 4, 2},
        {5, 6, 1},
        {4, 3, 2}
    };

    Solution s;
    cout << s.maximumChocolates(m, n, grid) << endl;

    return 0;
}
