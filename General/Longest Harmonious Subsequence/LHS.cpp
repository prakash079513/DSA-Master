#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> freq;
        for (int num : nums) freq[num]++;
        int maxLen = 0;
        for (auto& [num, count] : freq) {
            if (freq.count(num + 1)) {
                maxLen = max(maxLen, count + freq[num + 1]);
            }
        }
        return maxLen;
    }
};

int main() {
    vector<int> nums = {1,3,2,2,5,2,3,7};
    Solution s1;
    cout << s1.findLHS(nums) << endl;
    return 0;
}
