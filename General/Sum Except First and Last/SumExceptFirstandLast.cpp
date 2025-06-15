#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int sumExceptFirstAndLast(vector<int>& arr) {
        if(arr.size() <= 2) return 0;
        return accumulate(arr.begin() + 1, arr.end() - 1, 0);
    }
};

int main() {
    vector<int> arr = {5, 24, 39, 60, 15, 28, 27, 40, 50, 90};
    Solution s1;
    cout << s1.sumExceptFirstAndLast(arr);
    return 0;
}