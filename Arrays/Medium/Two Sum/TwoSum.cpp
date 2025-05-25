#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> mp; // number -> index

        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            if (mp.find(complement) != mp.end()) {
                return {mp[complement], i};
            }
            mp[nums[i]] = i;
        }
        return {}; // no solution found
    }
};

int main() {
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    Solution s1;
    vector<int> result = s1.twoSum(nums, target);
    if (!result.empty()) {
        cout << result[0] << " " << result[1];
    } else {
        cout << "No solution";
    }
    return 0;
}
