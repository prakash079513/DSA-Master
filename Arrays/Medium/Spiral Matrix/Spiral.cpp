#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> printSpiral(const vector<vector<int>> &mat) {
        if (mat.empty() || mat[0].empty()) return {};
        int n = mat.size(), m = mat[0].size();
        vector<int> ans;
        ans.reserve(n * m);
        int top = 0, bottom = n - 1, left = 0, right = m - 1;

        while (top <= bottom && left <= right) {
            for (int i = left; i <= right; ++i) ans.push_back(mat[top][i]);
            ++top;
            for (int i = top; i <= bottom; ++i) ans.push_back(mat[i][right]);
            --right;
            if (top <= bottom) {
                for (int i = right; i >= left; --i) ans.push_back(mat[bottom][i]);
                --bottom;
            }
            if (left <= right) {
                for (int i = bottom; i >= top; --i) ans.push_back(mat[i][left]);
                ++left;
            }
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<vector<int>> mat {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    Solution s;
    for (int x : s.printSpiral(mat)) cout << x << ' ';
    cout << '\n';
    return 0;
}
