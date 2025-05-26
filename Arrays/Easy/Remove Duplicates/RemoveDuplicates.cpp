#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        int index = 0; 
        
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] != nums[index]) {
                nums[++index] = nums[i]; 
            }
        }
        return index + 1;
    }
};

int main() {
  
    vector<int> nums = {1, 1, 2, 2, 3, 4, 4, 4, 5};
    Solution s;
    int len = s.removeDuplicates(nums);
    
    cout << "Length after removing duplicates: " << len << endl;
    cout << "Array contents: ";
    for (int i = 0; i < len; ++i) {
        cout << nums[i] << " ";
    }
    cout << endl;
    
    return 0;
}
