# Subarrays with K Different Integers

**Leetcode #992**

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

Given an integer array nums and an integer k, return the number of good subarrays of nums.

A good subarray is a subarray where the number of distinct integers is EXACTLY k.

## Brute Force Approach

- Generate every possible subarray using two loops.
- Use a set to track distinct numbers in each subarray.
- If the size of the set is exactly k, increment count.
- Very slow because each subarray re-computes distinct counts.

### Code

```cpp
int subarraysWithKDistinct(vector<int>& nums, int k) {
    int n = nums.size();
    int count = 0;

    for(int i = 0; i < n; i++) {
        unordered_set<int> st;
        for(int j = i; j < n; j++) {
            st.insert(nums[j]);
            if(st.size() == k) count++;
            else if(st.size() > k) break;
        }
    }
    return count;
}
```

### Complexity Analysis

**Time Complexity:** `O(n^2)` – We try all subarrays.

**Space Complexity:** `O(n)` – The set may grow up to n in worst case.

## Prefix Sliding (Counting Distinct On The Go)

- For each start index i:
  - Keep a frequency map.
  - Expand end j and keep counting distinct numbers.
  - Once distinct > k, stop.
- Faster than brute force because we avoid re-starting the count fully each time.

### Code

```cpp
int subarraysWithKDistinct(vector<int>& nums, int k) {
    int n = nums.size();
    int count = 0;

    for(int i = 0; i < n; i++) {
        unordered_map<int,int> freq;
        int distinct = 0;

        for(int j = i; j < n; j++) {
            if(freq[nums[j]] == 0) distinct++;
            freq[nums[j]]++;

            if(distinct == k) count++;
            else if(distinct > k) break;
        }
    }
    return count;
}
```

### Complexity Analysis

**Time Complexity:** `O(n^2)` – Still quadratic, but slightly fewer operations.

**Space Complexity:** `O(n)` – Frequency map.

## Optimal Sliding Window

### Core Idea

Instead of counting subarrays with **exactly k distinct**,

we compute:

**atMost(x): number of subarrays with ≤ x distinct elements**

Then:

**exactly(k) = atMost(k) – atMost(k – 1)**

**Why this works**

- atMost(k) includes all subarrays with 1..k distinct.
- atMost(k−1) includes all subarrays with 1..k−1 distinct.
- Subtracting removes all smaller distinct-count subarrays.
- Only subarrays with exactly k distinct remain.

**How atMost(k) Works (Sliding Window)**

- Use two pointers (l, r).
- Expand r, add nums[r] into freq map.
- If distinct > k: shrink from left until valid again.
- Every time window is valid, add (r − l + 1) to answer because:
  - All subarrays **ending at r** and starting between l..r are valid.

### Dry Run Example (nums = [1,2,1,2,3], k = 2)

We compute:

- atMost(2)
- atMost(1)
- exactly(2) = atMost(2) – atMost(1)

### atMost(2)

| Window                            | Distinct                                    | Count Increase | Total |
| --------------------------------- | ------------------------------------------- | -------------- | ----- |
| [1]                               | {1}                                         | +1             | 1     |
| [1,2]                             | {1,2}                                       | +2             | 3     |
| [1,2,1] // ending at 1            | {1,2}                                       | +3             | 6     |
| [1,2,1,2]                         | {1,2}                                       | +4             | 10    |
| [1,2,1,2,3] → shrink to [2,1,2,3] | {1,2,3}→invalid→shrink→{1,2,3} shrink→{2,3} | +2             | 12    |

atMost(2) = 12

### atMost(1)

| Window                          | Distinct | Count Increase | Total |
| ------------------------------- | -------- | -------------- | ----- |
| [1]                             | {1}      | +1             | 1     |
| [1,2] → invalid → shrink to [2] | {2}      | +1             | 2     |
| [2,1] → invalid → shrink to [1] | {1}      | +1             | 3     |
| [1,2] → invalid → shrink to [2] | +1       | 4              |       |
| [2,3] → invalid → shrink to [3] | +1       | 5              |       |

atMost(1) = 5

### Final

exactly(2) = 12 − 5 = 7

### Code

```cpp
int atMost(vector<int>& nums, int k) {
    unordered_map<int,int> freq;
    int l = 0, count = 0, distinct = 0;

    for(int r = 0; r < nums.size(); r++) {
        if(freq[nums[r]] == 0) distinct++;
        freq[nums[r]]++;

        while(distinct > k) {
            freq[nums[l]]--;
            if(freq[nums[l]] == 0) distinct--;
            l++;
        }

        count += (r - l + 1);
    }
    return count;
}

int subarraysWithKDistinct(vector<int>& nums, int k) {
    return atMost(nums, k) - atMost(nums, k - 1);
}
```

### Complexity Analysis

**Time Complexity:** `O(n)` – Each index is visited at most twice (expand + shrink).

**Space Complexity:** `O(n)` – Frequency map per sliding window.

---

THE END
