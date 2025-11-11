# Range Sum Query – Immutable

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

You are given an integer array `nums`.

Implement the class `NumArray` that supports the following operation:

- `NumArray(vector<int>& nums)` – Initialize the object with the integer array `nums`.
- `int sumRange(int left, int right)` – Return the sum of the elements of `nums` between indices `left` and `right` inclusive (i.e., `sum(nums[left] ... nums[right])`).

---

### Approach

**Prefix Sum Technique**

- Precompute a prefix sum array `prefix` where `prefix[i]` stores the sum of all elements up to index `i - 1` in `nums`.
- Specifically:
  - `prefix[0] = 0`
  - For each `i` from `1` to `n`, set `prefix[i] = prefix[i - 1] + nums[i - 1]`.
- To find the sum from `left` to `right`, use:
  - `sumRange(left, right) = prefix[right + 1] - prefix[left]`.

This avoids recomputing sums repeatedly, making each query efficient.

---

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class NumArray {
    vector<int> prefix;
public:
    NumArray(vector<int>& nums) {
        int n = nums.size();
        prefix.resize(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            prefix[i] = prefix[i - 1] + nums[i - 1];
        }
    }

    int sumRange(int left, int right) {
        return prefix[right + 1] - prefix[left];
    }
};

int main() {
    vector<int> nums = {-2, 0, 3, -5, 2, -1};
    NumArray s1(nums);
    cout << s1.sumRange(0, 2) << endl;  // Output: 1
    cout << s1.sumRange(2, 5) << endl;  // Output: -1
    cout << s1.sumRange(0, 5) << endl;  // Output: -3
    return 0;
}
```

---

### Complexity Analysis

**Time Complexity:**

- Preprocessing: `O(n)` – Build prefix sum array.
- Each Query: `O(1)` – Direct subtraction from prefix array.

**Space Complexity:** `O(n)` – Prefix array to store cumulative sums.

---

THE END
