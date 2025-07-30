#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(i == 0 && j == 0) {
                    dp[i][j] = matrix[i][j];
                } else {
                    int up = (i > 0) ? dp[i-1][j] : INT_MAX;
                    int left = (j > 0) ? dp[i][j-1] : INT_MAX;
                    dp[i][j] = matrix[i][j] + min(up, left);
                }
            }
        }

        return dp[m-1][n-1];
    }
};

int main() {
    vector<vector<int>> matrix = {
        {1, 3, 1},
        {1, 5, 1},
        {4, 2, 1}
    };

    Solution s1;
    cout << s1.minPathSum(matrix) << endl;
    return 0;
}
