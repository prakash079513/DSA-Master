#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumPathSum(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<int> next(triangle[n-1]);
        for(int i = n - 2; i >= 0; --i) {
            vector<int> curr(i + 1);
            for(int j = 0; j <= i; ++j) {
                int down = next[j];
                int diag = next[j + 1];
                curr[j] = triangle[i][j] + min(down, diag);
            }
            next = curr;
        }
        return next[0];
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
