#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int f(int i, int j, vector<vector<int>>& mat, int n) {
        if(i == n - 1) return mat[i][j];
        int down = mat[i][j] + f(i + 1, j, mat, n);
        int diag = mat[i][j] + f(i + 1, j + 1, mat, n);
        return min(down, diag);
    }

    int minimumPathSum(vector<vector<int>>& triangle) {
        int n = triangle.size();
        return f(0, 0, triangle, n);
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
