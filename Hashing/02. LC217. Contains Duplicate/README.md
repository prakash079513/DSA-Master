## **217. Contains Duplicate**

Author: Prakash JC

## Problem Statement

Given an integer array `nums`, return **true** if any value appears **at least twice** in the array, and return **false** if every element is distinct.

---

### Key Takeaway

- Use a set. If it's already in the set, return. Else insert into the set.

## Brute Force Approach

### Approach

- Use two nested loops
- For each element `i`, compare with every element `j > i`
- If any pair is equal → return `true`
- If no duplicates found → return `false`

**Time Complexity:** `O(n^2)`
**Space Complexity:** `O(1)`

## Optimal Approach – HashSet

### Key Observation

- We only need to know if an element has been seen before
- A set provides `O(1)` average lookup and insertion

### Approach

- Create an empty set `st`
- Traverse array:
  - If `nums[i]` already exists in set → return `true`
  - Else insert it into set

- If traversal completes → return `false`

---

## Code

```cpp
bool containsDuplicate(vector<int>& nums) {
    unordered_set<int> st;

    for (int i = 0; i < nums.size(); i++) {
        if (st.find(nums[i]) != st.end())
            return true;

        st.insert(nums[i]);
    }

    return false;
}
```

---

**Time Complexity:** `O(n)` – single pass with constant time operations

**Space Complexity:** `O(n)` – set stores elements

---

## Interview Notes

- Sorting approach (`O(n log n)`) is valid but not optimal
- HashSet solution is expected
- Early return improves efficiency

---

THE END
