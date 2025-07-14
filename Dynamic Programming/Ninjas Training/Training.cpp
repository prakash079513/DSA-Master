#include <bits/stdc++.h>
using namespace std;

class Solution {
public: 
    int ninjaTraining(int n, vector<vector<int>>& points) {
        vector<int> prev(4, 0);
        prev[0] = max(points[0][1], points[0][2]);
        prev[1] = max(points[0][0], points[0][2]);
        prev[2] = max(points[0][0], points[0][1]);
        prev[3] = max({points[0][0], points[0][1], points[0][2]});

        for (int day = 1; day < n; day++) {
            vector<int> temp(4, 0);
            for (int last = 0; last < 4; last++) {
                for (int task = 0; task < 3; task++) {
                    if (task != last) {
                        temp[last] = max(temp[last], points[day][task] + prev[task]);
                    }
                }
            }
            prev = temp;
        }

        return prev[3];
    }
};

int main() {
    vector<vector<int>> points = {{10, 40, 70},
                                  {20, 50, 80},
                                  {30, 60, 90}};
    int n = points.size();
    Solution s1;
    cout << s1.ninjaTraining(n, points);
    return 0;
}
