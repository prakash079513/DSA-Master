# Missing Element

Author: [Prakash JC](https://github.com/prakash079513)

### Problem Statement

Given an integer `n` and an array of size `n-1` containing distinct numbers from `1` to `n`, find the missing number.

---

### Approach 1: Sorting + Linear Check

- Sort the array.
- Traverse the sorted array and check if each element is followed by the next consecutive number.
- If a gap is found → return the missing number.
- If no gap → the missing number is either `1` or `n`.

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int missingNumberSort(vector<int>& nums, int n) {
        sort(nums.begin(), nums.end());
        for (int i = 0; i < n - 2; i++) {
            if (nums[i + 1] != nums[i] + 1) {
                return nums[i] + 1;
            }
        }
        // If no gap found, missing is at boundary
        if (nums[0] != 1) return 1;
        return n;
    }
};
```

### Complexity Analysis

- **Time Complexity:** `O(n log n)` – sorting dominates.
- **Space Complexity:** `O(1)` if in-place sort.

---

### Approach 2: Sum Formula

- The sum of first `n` natural numbers is `n*(n+1)/2`.
- Compute sum of given array.
- Missing number = total sum − array sum.

### Code

```cpp
class Solution2 {
public:
    int missingNumberSum(vector<int>& nums, int n) {
        long long total = (1LL * n * (n + 1)) / 2;
        long long arrSum = 0;
        for (int x : nums) arrSum += x;
        return total - arrSum;
    }
};
```

### Complexity Analysis

- **Time Complexity:** `O(n)` – single pass for sum.
- **Space Complexity:** `O(1)`.

---

### Approach 3: XOR Method

- XOR of all numbers from `1..n` with all array elements will leave only the missing number (since duplicates cancel out).

### Code

```cpp
class Solution3 {
public:
    int missingNumberXor(vector<int>& nums, int n) {
        int xorAll = 0, xorArr = 0;
        for (int i = 1; i <= n; i++) xorAll ^= i;
        for (int x : nums) xorArr ^= x;
        return xorAll ^ xorArr;
    }
};
```

### Complexity Analysis

- **Time Complexity:** `O(n)` – one pass over `1..n` and one over the array.
- **Space Complexity:** `O(1)`.

---

THE END
