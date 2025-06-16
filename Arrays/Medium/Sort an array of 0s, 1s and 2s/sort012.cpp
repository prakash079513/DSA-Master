#include <bits/stdc++.h>
using namespace std;

class Solution {
public: 
    void sort012(vector<int> &arr) { 
        int n = arr.size();
        int lo = 0, hi = n - 1, mid = 0;

        while (mid <= hi) {
            if (arr[mid] == 0)
                swap(arr[lo++], arr[mid++]);
            else if (arr[mid] == 1)
                mid++;
            else
                swap(arr[mid], arr[hi--]);
        }
    }
};

int main() {
    vector<int> arr = {0, 1, 2, 0, 1, 2};
    Solution s1;
    s1.sort012(arr); 

    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
        
    return 0;
}
