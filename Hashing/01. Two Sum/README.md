## **1. Two Sum**

Author: Prakash JC

---

## Problem Statement

Given an array of integers `nums` and an integer `target`, return indices of the two numbers such that they add up to `target`.

- Each input has **exactly one solution**
- You may not use the same element twice
- Return the answer in any order

---

### Key Takeaway

- Use hashmap to store value → index and check complement in one pass.

---

## Brute Force Approach

### Approach

- Use two nested loops
- For each element `i`, check every element `j > i`
- If `nums[i] + nums[j] == target`, return `{i, j}`

**Time Complexity:** `O(n^2)`
**Space Complexity:** `O(1)`

---

## Optimal Approach – HashMap

### Key Observation

- Instead of checking all pairs, we can store previously seen numbers
- For each number `x`, we need `target - x`
- If that value already exists → we found the answer

### Approach

- Create a hashmap `mp` (value → index)
- Traverse array:
  - Compute `rem = target - nums[i]`
  - If `rem` exists in map → return `{mp[rem], i}`
  - Else store `nums[i]` with index `i`

- Return result

## Code

```cpp
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> mp;

    for (int i = 0; i < nums.size(); i++) {
        int rem = target - nums[i];

        if (mp.find(rem) != mp.end()) {
            return {mp[rem], i};
        }

        mp[nums[i]] = i;
    }

    return {};
}
```

---

**Time Complexity:** `O(n)` – single pass with hashmap lookups
**Space Complexity:** `O(n)` – hashmap storage

---

## Interview Notes

- Do **not** sort → indices will be lost
- Always use hashmap for optimal solution
- Think in terms of **complement**
- One-pass solution is expected

---

THE END
