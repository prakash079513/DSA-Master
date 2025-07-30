#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumPathSum(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<vector<int>> dp(n, vector<int>(n));
        for(int j = 0; j < n; ++j) dp[n-1][j] = triangle[n-1][j];
        for(int i = n - 2; i >= 0; --i) {
            for(int j = 0; j <= i; ++j) {
                int down = dp[i+1][j];
                int diag = dp[i+1][j+1];
                dp[i][j] = triangle[i][j] + min(down, diag);
            }
        }
        return dp[0][0];
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
