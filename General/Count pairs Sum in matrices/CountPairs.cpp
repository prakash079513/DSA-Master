#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countPairs(vector<vector<int>> &mat1, vector<vector<int>> &mat2, int x) {
        int n = mat1.size();
        unordered_set<int> st;
        int count = 0;

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                st.insert(mat2[i][j]);

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (st.count(x - mat1[i][j]))
                    count++;

        return count;
    }
};

int main() {
    int n = 3, x = 21;
    vector<vector<int>> mat1 = {{1, 5, 6}, {8, 10, 11}, {15, 16, 18}};
    vector<vector<int>> mat2 = {{2, 4, 7}, {9, 10, 12}, {13, 16, 20}};

    Solution s1;
    int result = s1.countPairs(mat1, mat2, x);
    cout << result << endl;

    return 0;
}
