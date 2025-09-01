#include <bits/stdc++.h>
using namespace std;

class Solution {
public: 
    bool subsetSumToK(int n, int k, vector<int>& arr) {
        vector<bool> prev(k + 1, false), curr(k + 1, false);

        // base case
        prev[0] = true;
        if (arr[0] <= k) prev[arr[0]] = true;

        for (int i = 1; i < n; i++) {
            curr[0] = true; // sum 0 is always true
            for (int target = 1; target <= k; target++) {
                bool notTake = prev[target];
                bool take = false;
                if (arr[i] <= target) take = prev[target - arr[i]];
                curr[target] = take || notTake;
            }
            prev = curr; // move to next row
        }
        return prev[k];
    }
};

int main() {
    int n = 4, k = 5;
    vector<int> arr = {1, 2, 3, 4};
    Solution s1;
    cout << (s1.subsetSumToK(n, k, arr) ? "True" : "False");
    return 0;
}
