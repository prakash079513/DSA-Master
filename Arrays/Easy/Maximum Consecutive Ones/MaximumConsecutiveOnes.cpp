#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int maxCount = 0;
        int currentCount = 0;
        
        for (int num : nums) {
            if (num == 1) {
                currentCount++;
                maxCount = max(maxCount, currentCount);
            } else {
                currentCount = 0;
            }
        }
        
        return maxCount;
    }
};

int main() {
    vector<int> prices = {1, 1, 0, 1, 1, 1};
    Solution s;
    int maxConsecutiveOnes = s.findMaxConsecutiveOnes(prices);
    cout << "Maximum Consecutive Ones: " << maxConsecutiveOnes << endl;
    
    vector<int> prices2 = {1, 0, 1, 1, 0, 1};
    int maxConsecutiveOnes2 = s.findMaxConsecutiveOnes(prices2);
    cout << "Maximum Consecutive Ones: " << maxConsecutiveOnes2 << endl;
    
    return 0;
}
