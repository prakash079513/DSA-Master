#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestSubarrayWithSumK(vector<int>& arr, long long k) {
        int n = arr.size();
        int left = 0, right = 0, maxLen = 0;
        long long sum = arr[0];

        while (right < n) {
            
            while (left <= right && sum > k) {
                sum -= arr[left];
                left++;
            }

            if (sum == k) {
                maxLen = max(maxLen, right - left + 1);
            }

            right++;
            if (right < n) sum += arr[right];
        }

        return maxLen;
    }
};

int main() {
    int N = 5;
    long long K = 10;
    vector<int> arr = {2, 3, 5, 1, 9};

    Solution s1;
    int result = s1.longestSubarrayWithSumK(arr, K);
    cout << "The length of the longest subarray is: " << result << "\n";
    return 0;
}
