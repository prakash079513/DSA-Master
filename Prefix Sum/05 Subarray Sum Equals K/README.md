# **Subarray Sum Equals K**

**LeetCode #560**

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

Given an array of integers `nums` and an integer `k`, return *the total number of subarrays whose sum equals to* `k`.

A subarray is a contiguous **non-empty** sequence of elements within an array.

**Example 1:**

```
Input: nums = [1,1,1], k = 2
Output: 2
```

**Example 2:**

```
Input: nums = [1,2,3], k = 3
Output: 2
```

# Editorial

## **Brute Force (Triple Loop)**

### **Approach**

- Consider every possible subarray using all pairs `(i, j)` where `i ≤ j`.
- For each pair, compute the sum by looping through all elements from `i` to `j`.
- Compare sum with `k` and increment count if equal.
- Extremely slow because the sum is recomputed repeatedly.

---

### **Code**

```cpp
int subarraySum(vector<int>& nums, int k) {
    int n = nums.size(), count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int sum = 0;
            for (int x = i; x <= j; x++) sum += nums[x];
            if (sum == k) count++;
        }
    }
    return count;
}
```

---

### **Complexity Analysis**

**Time Complexity:** `O(n^3)` – Three nested loops.

**Space Complexity:** `O(1)` – No extra memory used.

## **Prefix Sum Array (Double Loop)**

### **Approach**

- Create a prefix sum array such that `pref[i]` = sum of first `i` elements.
- Any subarray sum from `i` to `j` becomes `pref[j+1] - pref[i]`.
- Iterate all `(i, j)` pairs but compute sum in `O(1)` using prefix.
- Faster because repeated summing is avoided.

---

### **Code**

```cpp
int subarraySum(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> pref(n+1, 0);
    for (int i = 1; i <= n; i++) pref[i] = pref[i-1] + nums[i-1];

    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int sum = pref[j+1] - pref[i];
            if (sum == k) count++;
        }
    }
    return count;
}
```

---

### **Complexity Analysis**

**Time Complexity:** `O(n^2)` – Two loops.

**Space Complexity:** `O(n)` – Prefix array.

## **Without Extra Space (Two Loops + Running Sum)**

### **Approach**

- Fix a starting index `i`.
- Maintain a running sum `curr` as you expand the subarray by increasing `j`.
- Add `nums[j]` to `curr` and compare with `k` at each step.
- Reset `curr` to 0 when moving `i` to the next index.

---

### **Code**

```cpp
int subarraySum(vector<int>& nums, int k) {
    int n = nums.size(), count = 0;
    for (int i = 0; i < n; i++) {
        int curr = 0;
        for (int j = i; j < n; j++) {
            curr += nums[j];
            if (curr == k) count++;
        }
    }
    return count;
}
```

---

### **Complexity Analysis**

**Time Complexity:** `O(n^2)` – Double loop with running sum.

**Space Complexity:** `O(1)` – No extra memory.

## **HashMap + Prefix Sum (Optimal)**

### **Approach**

- Maintain a running prefix sum `prefix`.
- For each index, check how many times `prefix - k` has occurred before.
- Those occurrences correspond to valid subarrays ending at current index.
- Store all prefix sums in a hash map with their frequencies.

---

### **Code**

```cpp
int subarraySum(vector<int>& nums, int k) {
    unordered_map<int,int> mp;
    mp[0] = 1;
    int prefix = 0, count = 0;

    for (int x : nums) {
        prefix += x;
        if (mp.find(prefix - k) != mp.end()) count += mp[prefix - k];
        mp[prefix]++;
    }

    return count;
}
```

---

### **Complexity Analysis**

**Time Complexity:** `O(n)` – One pass with constant-time hash lookups.

**Space Complexity:** `O(n)` – Store prefix frequencies.

---

THE END
