#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxPathSum(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<int> next(matrix[m - 1]);

        for (int i = m - 2; i >= 0; i--) {
            vector<int> curr(n);
            for (int j = 0; j < n; j++) {
                int down = next[j];
                int leftDiag = (j - 1 >= 0) ? next[j - 1] : -1e9;
                int rightDiag = (j + 1 < n) ? next[j + 1] : -1e9;

                curr[j] = matrix[i][j] + max({down, leftDiag, rightDiag});
            }
            next = curr;
        }

        return *max_element(next.begin(), next.end());
    }
};

int main() {
    vector<vector<int>> matrix = {
        {10, 10, 2, 0, 20, 4},
        {1, 0, 0, 30, 2, 5},
        {0, 10, 4, 0, 2, 0},
        {1, 0, 2, 20, 0, 4}
    };
    
    Solution s1;
    cout << s1.maxPathSum(matrix) << endl;
    return 0;
}
