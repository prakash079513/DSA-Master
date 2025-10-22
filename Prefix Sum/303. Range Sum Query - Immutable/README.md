## **303. Range Sum Query - Immutable**

Author: [Prakash JC](https://prakash079513.github.io)

## **Problem Statement:**

[Link](https://leetcode.com/problems/range-sum-query-immutable/description/)

Given an integer array `nums`, handle multiple queries of the following type:

Calculate the sum of the elements of `nums` between indices `left` and `right` inclusive where `left <= right`.

Implement the `NumArray` class:

- `NumArray(int[] nums)` Initializes the object with the integer array `nums`.
- `int sumRange(int left, int right)` Returns the sum of the elements of `nums` between indices `left` and `right` inclusive (i.e. `nums[left] + nums[left + 1] + ... + nums[right]`).

**Example 1:**

Input

`["NumArray", "sumRange", "sumRange", "sumRange"]`

`[[[-2, 0, 3, -5, 2, -1]], [0, 2], [2, 5], [0, 5]]`

Output

`[null, 1, -1, -3]`

**Explanation**

```
NumArray numArray = new NumArray([-2, 0, 3, -5, 2, -1]);
numArray.sumRange(0, 2); // return (-2) + 0 + 3 = 1
numArray.sumRange(2, 5); // return 3 + (-5) + 2 + (-1) = -1
numArray.sumRange(0, 5); // return (-2) + 0 + 3 + (-5) + 2 + (-1) = -3
```

**Constraints:**

- `1 <= nums.length <= 10⁴`
- `10⁵ <= nums[i] <= 10⁵`
- `0 <= left <= right < nums.length`
- At most `10⁴` calls will be made to `sumRange`.

---

### Editorial

## **Brute Force Approach**

**Idea:**

For each query `(left, right)`, iterate through all elements from `left` to `right` and compute the sum.

**Steps:**

1. Initialize `sum = 0`.
2. Loop from `i = left` to `i = right`, and add `nums[i]` to `sum`.
3. Return the sum.

**Drawback:**

This approach works but is inefficient because each query takes `O(n)` time, and with up to `10⁴` queries, total time could reach `10⁸` operations — too slow.

## **Optimal Approach (Prefix Sum / Cumulative Sum)**

**Core Idea:**

To make sum queries faster, precompute cumulative sums (prefix sums).

Let `prefix[i]` store the sum of all elements from index `0` to `i-1` (exclusive of `i`).

That is:

```
prefix[0] = 0
prefix[i] = prefix[i-1] + nums[i-1]   for i >= 1
```

Then,

Sum of elements from `left` to `right` = `prefix[right + 1] - prefix[left]`

**Why it works:**

Because `prefix[right + 1]` gives sum of elements up to `right`, and `prefix[left]` gives sum up to `left - 1`, subtracting gives exactly the range sum.

**Example:**

nums = [-2, 0, 3, -5, 2, -1]

prefix = [0, -2, -2, 1, -4, -2, -3]

Then:

- sumRange(2, 5) = prefix[6] - prefix[2] = -3 - (-2) = **1**

**Advantages:**

Once the prefix array is built in `O(n)`, each query takes only `O(1)` time.

## **Code**

```cpp
#include <bits/stdc++.h>
using namespace std;

class NumArray {
    vector<int> prefix;
public:
    NumArray(vector<int>& nums) {
        int n = nums.size();
        prefix.resize(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
    }

    int sumRange(int left, int right) {
        return prefix[right + 1] - prefix[left];
    }
};

int main() {
    vector<int> nums = {-2, 0, 3, -5, 2, -1};
    NumArray numArray(nums);
    cout << numArray.sumRange(0, 2) << endl; // 1
    cout << numArray.sumRange(2, 5) << endl; // -1
    cout << numArray.sumRange(0, 5) << endl; // -3
    return 0;
}
```

## **Complexity Analysis**

**Time Complexity:**

- Constructor: `O(n)` — for computing prefix sums once.
- Each query: `O(1)` — direct subtraction using prefix array.

**Space Complexity:**

- `O(n)` — for storing prefix sums.

---

THE END
