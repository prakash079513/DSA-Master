#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findLargestElement(vector<int>& arr) {
        int maxElement = arr[0];
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] > maxElement) {
                maxElement = arr[i];
            }
        }
        return maxElement;
    }
};

int main() {
    vector<int> arr = {3, 7, 2, 9, 5};
    Solution s1;
    cout << s1.findLargestElement(arr);
    return 0;
}
