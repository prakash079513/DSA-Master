#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void reverse(vector<int>& arr, int l, int r) {
        while (l < r) {
            swap(arr[l], arr[r]);
            l++;
            r--;
        }
    }

    void leftRotate(vector<int>& arr, int D) {
        int n = arr.size();
        D = D % n; // To handle D >= n
        if (D == 0) return;

        reverse(arr, 0, D - 1);       // Reverse first D elements
        reverse(arr, D, n - 1);       // Reverse rest of the elements
        reverse(arr, 0, n - 1);       // Reverse whole array
    }
};

int main() {
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7};
    int D = 2;

    Solution s1;
    s1.leftRotate(arr, D);

    for (int val : arr)
        cout << val << " ";
    cout << endl;

    return 0;
}
