# Maximum Size Subarray Sum Equals K

**LeetCode #325**

Author: [Prakash JC](https://prakash079513.github.io)

## **Problem Statement**

Given an integer array `nums` and an integer `k`, return the **maximum length** of a subarray that sums to `k`.

If no such subarray exists, return `0`.

## Editorial

## Brute Force (Triple Loop)

### **Approach**

- Generate all possible subarrays using indices `(i, j)`.
- For each subarray, compute its sum by looping through all elements from `i` to `j`.
- If the sum equals `k`, update the maximum length.
- Extremely slow because each sum is recomputed from scratch.

---

### **Code**

```cpp
int maxSubArrayLen(vector<int>& nums, int k) {
    int n = nums.size(), ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int sum = 0;
            for (int x = i; x <= j; x++) sum += nums[x];
            if (sum == k) ans = max(ans, j - i + 1);
        }
    }
    return ans;
}
```

---

### **Complexity Analysis**

**Time Complexity:** `O(n^3)` – All possible segments and sum inside.

**Space Complexity:** `O(1)` – No extra memory.

## Prefix Sum Array (Double Loop)

### **Approach**

- Build prefix sum array `pref`, where `pref[i]` = sum of first `i` elements.
- Subarray sum `i..j` becomes `pref[j+1] - pref[i]`.
- Iterate all `(i, j)` pairs and compare with `k`.
- Update answer with subarray length.

---

### **Code**

```cpp
int maxSubArrayLen(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> pref(n+1, 0);
    for (int i = 1; i <= n; i++) pref[i] = pref[i-1] + nums[i-1];

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int sum = pref[j+1] - pref[i];
            if (sum == k) ans = max(ans, j - i + 1);
        }
    }
    return ans;
}
```

---

### **Complexity Analysis**

**Time Complexity:** `O(n^2)` – Double loop with O(1) sum lookup.

**Space Complexity:** `O(n)` – Prefix array.

## Running Sum (Two Loops, No Extra Space)

### **Approach**

- Fix a start index `i`.
- Maintain a running sum `curr` while increasing the end index `j`.
- Add `nums[j]` each time and compare `curr` with `k`.
- If equal, update the maximum length.
- Reset `curr` when moving to the next start index.

---

### **Code**

```cpp
int maxSubArrayLen(vector<int>& nums, int k) {
    int n = nums.size(), ans = 0;
    for (int i = 0; i < n; i++) {
        int curr = 0;
        for (int j = i; j < n; j++) {
            curr += nums[j];
            if (curr == k) ans = max(ans, j - i + 1);
        }
    }
    return ans;
}
```

### **Complexity Analysis**

**Time Complexity:** `O(n^2)` – Two loops.

**Space Complexity:** `O(1)` – No additional memory.

## Optimal (HashMap + Prefix Sum)

### **Approach**

- Maintain prefix sum `prefix`.
- Track the **first occurrence** of each prefix value in a hash map.
- If `prefix - k` exists in the map:
  - A subarray with sum `k` exists from the stored index + 1 to current index.
  - Eg: [3 4 7 5 2 x x x], k = 7
  - Clearly at value 2: prefix sum = 14. First occurence of 14-7 = 7 is at index 2(say i). But the array 5, 2 is clearly staring from the index 3 i.e., i+1. Hence for prefix sum 7, store (7: 3) i.e., i+1.
  - Update maximum length accordingly.
- Store the prefix sum only the **first time** it appears to maximize subarray length.

This is the expected best solution.

---

### **Code**

```cpp
int maxSubArrayLen(vector<int>& nums, int k) {
    unordered_map<int,int> mp;
    mp[0] = 0;

    int prefix = 0, ans = 0;

    for (int i = 0; i < nums.size(); i++) {
        prefix += nums[i];

        if (mp.find(prefix - k) != mp.end())
            ans = max(ans, i + 1 - mp[prefix - k]);

        if (mp.find(prefix) == mp.end())
            mp[prefix] = i + 1;
    }

    return ans;
}
```

---

### **Complexity Analysis**

**Time Complexity:** `O(n)` – Each index processed once.

**Space Complexity:** `O(n)` – Map stores prefix sums.

---

THE END
