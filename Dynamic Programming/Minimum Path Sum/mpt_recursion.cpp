#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minPath(int i, int j, vector<vector<int>>& matrix) {
        if(i == 0 && j == 0) return matrix[0][0];
        if(i < 0 || j < 0) return INT_MAX;

        int up = minPath(i-1, j, matrix);
        int left = minPath(i, j-1, matrix);
        return matrix[i][j] + min(up, left);
    }

    int minPathSum(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        return minPath(m-1, n-1, matrix);
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
