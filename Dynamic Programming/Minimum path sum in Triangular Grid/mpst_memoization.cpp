#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int f(int i, int j, vector<vector<int>>& mat, int n, vector<vector<int>>& dp) {
        if(i == n - 1) return mat[i][j];
        if(dp[i][j] != -1) return dp[i][j];
        int down = mat[i][j] + f(i + 1, j, mat, n, dp);
        int diag = mat[i][j] + f(i + 1, j + 1, mat, n, dp);
        return dp[i][j] = min(down, diag);
    }

    int minimumPathSum(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));
        return f(0, 0, triangle, n, dp);
    }
};

int main() {
    vector<vector<int>> triangle = {
        {2},
        {3, 4},
        {6, 5, 7},
        {4, 1, 8, 3}
    };
    Solution s;
    cout << s.minimumPathSum(triangle);
    return 0;
}
