#include <bits/stdc++.h>
using namespace std;

class Solution {
public: 
    bool f(int index, int k, vector<int>& arr, vector<vector<int>>& dp) {
        // base cases
        if (k == 0) return true;
        if (index == 0) return arr[0] == k;

        if (dp[index][k] != -1) return dp[index][k];

        // not take
        bool notTake = f(index - 1, k, arr, dp);

        // take
        bool take = false;
        if (arr[index] <= k)
            take = f(index - 1, k - arr[index], arr, dp);

        return dp[index][k] = (take || notTake);
    }

    bool subsetSumToK(int n, int k, vector<int>& arr) {
        vector<vector<int>> dp(n, vector<int>(k + 1, -1));
        return f(n - 1, k, arr, dp);
    }
};

int main() {
    int n = 4, k = 5;
    vector<int> arr = {1, 2, 3, 4};
    Solution s1;
    cout << (s1.subsetSumToK(n, k, arr) ? "True" : "False");
    return 0;
}
