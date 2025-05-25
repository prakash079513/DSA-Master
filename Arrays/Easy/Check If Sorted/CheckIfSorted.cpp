#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isSorted(const vector<int>& arr) {
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] < arr[i - 1]) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    vector<int> arr = {1, 2, 2, 4, 5};
    Solution s1;
    cout << (s1.isSorted(arr) ? "Sorted" : "Not Sorted");
    return 0;
}
