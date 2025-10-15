#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void dfs(int row, int col, vector<vector<int>> &image, int newColor, int initColor) {
        int n = image.size();
        int m = image[0].size();
        image[row][col] = newColor;

        int delRow[] = {-1, 0, 1, 0};
        int delCol[] = {0, 1, 0, -1};

        for (int i = 0; i < 4; i++) {
            int r = row + delRow[i];
            int c = col + delCol[i];
            if (r >= 0 && r < n && c >= 0 && c < m && image[r][c] == initColor) {
                dfs(r, c, image, newColor, initColor);
            }
        }
    }

    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int newColor) {
        int initColor = image[sr][sc];
        if (initColor == newColor) return image;  // no need to fill

        dfs(sr, sc, image, newColor, initColor);
        return image;
    }
};

int main() {
    vector<vector<int>> image = {
        {1, 1, 1},
        {1, 1, 0},
        {1, 0, 1}
    };
    int sr = 1, sc = 1, newColor = 2;
    Solution s1;
    vector<vector<int>> result = s1.floodFill(image, sr, sc, newColor);

    for (auto &row : result) {
        for (auto &pixel : row) cout << pixel << " ";
        cout << endl;
    }
    return 0;
}
