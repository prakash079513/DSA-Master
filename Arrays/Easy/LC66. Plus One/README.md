# **66. Plus One**

Author: Prakash JC

## Problem Statement

You are given a non-empty array of digits representing a non-negative integer. The digits are stored such that the most significant digit is at the beginning, and each element contains a single digit. Increment the integer by one and return the resulting array of digits.

---

## Brute Force Approach

- Convert the digit array into a number
- Add 1 to the number
- Convert the number back into a digit array
- Return the result

**Why this is not recommended**

- Can overflow for large arrays
- Violates constraint thinking
- Interviewers reject this quickly

**Time Complexity: `O(n)`**
**Space Complexity: `O(n)`**

---

## Carry Simulation – In-place

### Key Observation

- Addition happens from the **last digit**
- If digit is less than 9 → just increment and stop
- If digit is 9 → becomes 0 and carry moves left.
- The next time if it is 9, add that carry to it, it means just set the number to 0.
- Hence, if a number is 9, just set it to 0.
- If all digits are 9 → result size increases by one

### Approach

- Traverse from right to left
- If current digit < 9
  - Increment it
  - Return array immediately

- Otherwise set digit to 0 and continue
- If loop finishes and nothing happens:
  - Create new array of size `n+1`
  - Put `1` at index 0 and rest 0s

---

## Code

```cpp
vector<int> plusOne(vector<int>& digits) {
    int n = digits.size();

    for (int i = n - 1; i >= 0; i--) {
        if (digits[i] < 9) {
            digits[i]++;
            return digits;
        }
        digits[i] = 0;
    }

    vector<int> ans(n + 1, 0);
    ans[0] = 1;
    return ans;
}
```

---

**Time Complexity:** `O(n)` – worst case all digits are 9

**Space Complexity:** `O(1)` – except output expansion case

---

THE END
