# Move Zeros to the End

Author: [Prakash JC](https://github.com/prakash079513)

### Problem Statement

Given an integer array `nums`, move all zeros to the end while maintaining the relative order of non-zero elements. Do this in-place without making a copy.

---

### Approach

### Idea

We need to shift all non-zero elements to the front in the same order and then fill the rest with zeros. Instead of using extra space or shifting repeatedly (which is costly), we use a **two-pass method** with a pointer `index` that tracks the position for the next non-zero element.

1. Initialize `index = 0`.
2. Traverse the array:
   - If the current element is non-zero, place it at `nums[index]` and increment `index`.
   - This ensures all non-zeros get compressed to the front.
3. After traversal, fill the remaining positions (from `index` to `n-1`) with zeros.

This method only requires one scan of the array + filling zeros.

---

### Dry Run (Case where first element is non-zero)

Input: `nums = [4, 0, 5, 0, 1]`

- Initial: `index = 0`
- i=0: `nums[0] = 4` → non-zero → `nums[0] = 4`, `index = 1`
- i=1: `nums[1] = 0` → skip
- i=2: `nums[2] = 5` → non-zero → `nums[1] = 5`, `index = 2` → `nums = [4, 5, 5, 0, 1]`
- i=3: `nums[3] = 0` → skip
- i=4: `nums[4] = 1` → non-zero → `nums[2] = 1`, `index = 3` → `nums = [4, 5, 1, 0, 1]`

Now fill from `index=3`:

- `nums[3] = 0`, `nums[4] = 0`

Final Output: `[4, 5, 1, 0, 0]`

---

## Code

### C++

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int index = 0;  // position to place next non-zero element

        // Move non-zero elements forward
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != 0) {
                nums[index++] = nums[i];
            }
        }

        // Fill the rest with zeros
        while (index < nums.size()) {
            nums[index++] = 0;
        }
    }
};

int main() {
    vector<int> nums = {4, 0, 5, 0, 1};
    Solution s1;
    s1.moveZeroes(nums);

    for (int x : nums) cout << x << " ";
    return 0;
}
```

### Python

```python
class Solution:
    def moveZeroes(self, nums):
        index = 0  # position to place next non-zero element

        # Move non-zero elements forward
        for i in range(len(nums)):
            if nums[i] != 0:
                nums[index] = nums[i]
                index += 1

        # Fill the rest with zeros
        while index < len(nums):
            nums[index] = 0
            index += 1

# Example usage
nums = [4, 0, 5, 0, 1]
Solution().moveZeroes(nums)
print(nums)

```

---

## Complexity Analysis

**Time Complexity:** `O(n)` – one pass to move elements and one pass to fill zeros.

**Space Complexity:** `O(1)` – in-place, no extra space used.

---

THE END
