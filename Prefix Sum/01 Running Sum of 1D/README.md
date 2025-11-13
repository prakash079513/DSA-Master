# Running Sum of 1D Array

**LeetCode #1480**

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

You are given an array `nums`.

We define the **running sum** of an array as:

`runningSum[i] = sum(nums[0] ... nums[i])`

Return the running sum of `nums`.

---

### Approach

- Initialize an empty result array `res` of the same size as `nums`.
- Set `res[0] = nums[0]`.
- Iterate from index `1` to `n-1`:
  - For each index `i`, compute `res[i] = res[i-1] + nums[i]`.
- Return the result array.

This accumulates the sum as we move through the array, avoiding redundant summations.

---

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        vector<int> res(nums.size());
        res[0] = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            res[i] = res[i - 1] + nums[i];
        }
        return res;
    }
};

int main() {
    vector<int> nums = {1, 2, 3, 4};
    Solution s1;
    vector<int> ans = s1.runningSum(nums);
    for (int x : ans) cout << x << " ";
    return 0;
}
```

---

### Complexity Analysis

**Time Complexity:** `O(n)` – Each element is visited once.

**Space Complexity:** `O(n)` – Output array of same size as input.

_(In-place version can achieve `O(1)` extra space by updating `nums` directly.)_

---

### Optional In-place Version

```cpp
vector<int> runningSum(vector<int>& nums) {
    for (int i = 1; i < nums.size(); i++) {
        nums[i] += nums[i - 1];
    }
    return nums;
}
```

---

THE END
