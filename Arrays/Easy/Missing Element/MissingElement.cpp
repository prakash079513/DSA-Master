#include <bits/stdc++.h>
using namespace std;

class Solution {
public: 
    int findMissingNumber(vector<int>& nums) { 
        int n = nums.size() + 1;
        int totalSum = n * (n + 1) / 2;
        int currentSum = 0;
        
        for (int num : nums) {
            currentSum += num;
        }
        
        return totalSum - currentSum;
    }
};

int main() {
    vector<int> nums = {3, 7, 1, 2, 8, 4, 5};
    Solution s1;
    cout << "The missing number is: " << s1.findMissingNumber(nums) << endl; 
    return 0;
}
