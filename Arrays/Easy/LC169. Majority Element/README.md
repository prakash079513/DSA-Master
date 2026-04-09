## **169. Majority Element**

Author: Prakash JC

### Problem Statement

Given an array `nums` of size `n`, return the **majority element**.

The majority element is the element that appears **more than ⌊n / 2⌋ times**.

You may assume that the majority element **always exists** in the array.

---

### Brute Force Approach

- For every element, count its frequency by scanning the entire array
- If frequency > n/2, return that element

**Time Complexity: `O(n^2)`**

**Space Complexity: `O(1)`**

---

### Moore’s Voting Algorithm – Optimal

#### Key Observation

- Majority element appears **more than half** the time
- Cancelling one majority element with one non-majority element still leaves majority intact
- Final remaining candidate must be the majority element

### Approach

- Maintain two variables:
  - `candidate` → potential majority element
  - `count` → balance counter
- Traverse the array:
  - If `count == 0`, set `candidate = nums[i]`
  - If `nums[i] == candidate`, increment `count`
  - Else decrement `count`
- After traversal, `candidate` holds the majority element

---

### Dry Run

Array: `3 3 3 2 3 2`

| Step | Element | Candidate | Count |
| ---- | ------- | --------- | ----- |
| 1    | 3       | 3         | 1     |
| 2    | 3       | 3         | 2     |
| 3    | 3       | 3         | 3     |
| 4    | 2       | 3         | 2     |
| 5    | 3       | 3         | 3     |
| 6    | 2       | 3         | 2     |

Final Candidate = **3**

---

### Code (Moore’s Voting)

```cpp
int majorityElement(vector<int>& nums) {
    int candidate = 0;
    int count = 0;

    for (int i = 0; i < nums.size(); i++) {
        if (count == 0)
            candidate = nums[i];

        if (nums[i] == candidate)
            count++;
        else
            count--;
    }
    return candidate;
}
```

---

### Map Approach (Alternative)

- Count frequency using a hashmap
- Return element whose frequency > n/2

```cpp
int majorityElement(vector<int>& nums) {
    unordered_map<int, int> mp;

    for (int i = 0; i < nums.size(); i++) {
        mp[nums[i]]++;
        if (mp[nums[i]] > nums.size() / 2)
            return nums[i];
    }
    return -1;
}
```

---

**Time Complexity:** `O(n)` – single traversal

**Space Complexity:** `O(1)` – for Moore’s Voting

---

THE END
