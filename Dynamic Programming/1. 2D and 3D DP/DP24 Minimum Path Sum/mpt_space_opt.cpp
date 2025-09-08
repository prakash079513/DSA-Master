#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        vector<int> prev(n, 0);

        for(int i = 0; i < m; i++) {
            vector<int> curr(n, 0);
            for(int j = 0; j < n; j++) {
                if(i == 0 && j == 0) {
                    curr[j] = matrix[i][j];
                } else {
                    int up = (i > 0) ? prev[j] : INT_MAX;
                    int left = (j > 0) ? curr[j-1] : INT_MAX;
                    curr[j] = matrix[i][j] + min(up, left);
                }
            }
            prev = curr;
        }

        return prev[n-1];
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
