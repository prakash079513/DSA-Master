#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int index = 0;  // Points to the position to place the next non-zero element

        // Move all non-zero elements to the front
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != 0) {
                nums[index++] = nums[i];
            }
        }

        // Fill the remaining part with zeros
        while (index < nums.size()) {
            nums[index++] = 0;
        }
    }
};

int main() {
    vector<int> nums = {0, 1, 0, 3, 12};
    Solution s1;
    s1.moveZeroes(nums);

    for (int x : nums) {
        cout << x << " ";
    }

    return 0;
}
