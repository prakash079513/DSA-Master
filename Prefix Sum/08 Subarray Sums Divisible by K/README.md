# **Subarray Sums Divisible by K**

**LeetCode #974**

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

Given an integer array nums and an integer k, return the number of non-empty subarrays whose sum is divisible by k.

A subarray sum is divisible by k if (sum % k == 0).

## Brute Force Approach

- For every start index i:
  - For every end index j ≥ i:
    - Compute the subarray sum via adding one by one.
    - Check if sum % k == 0.
- Straightforward but slow.

### Code

```cpp
int subarraysDivByK(vector<int>& nums, int k) {
    int n = nums.size();
    int count = 0;

    for(int i = 0; i < n; i++) {
        int sum = 0;
        for(int j = i; j < n; j++) {
            sum += nums[j];
            if(sum % k == 0) count++;
        }
    }
    return count;
}
```

### Complexity Analysis

**Time Complexity:** `O(n^2)` – All subarrays.

**Space Complexity:** `O(1)` – Only sum variable.

## Prefix Sum (Without Using Mod Grouping)

- Compute prefix sum array.
- For any subarray (i,j):
  - sum = prefix[j] − prefix[i−1]
  - Check if sum % k == 0.
- Still quadratic because we check all i,j pairs.

### Code

```cpp
int subarraysDivByK(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> prefix(n+1, 0);

    for(int i = 0; i < n; i++)
        prefix[i+1] = prefix[i] + nums[i];

    int count = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j <= n; j++) {
            if((prefix[j] - prefix[i]) % k == 0)
                count++;
        }
    }
    return count;
}
```

### Complexity Analysis

**Time Complexity:** `O(n^2)` – Still checking all subarrays.

**Space Complexity:** `O(n)` – Prefix sum array.

## Optimal Prefix Mod + HashMap Expected Solution

- If two prefix sums have the same remainder modulo k, then the subarray between them is divisible by k.
- Let prefix sum up to index i be P[i].
- Remainder: r = ((P[i] % k) + k) % k (handle negatives)
- If remainder r has appeared freq[r] times before, then:
  - All those previous positions create valid subarrays ending at i.

Key idea:

**Subarray sum (i,j) is divisible by k if prefix[j] % k == prefix[i−1] % k.**

### Steps

- Maintain running prefix sum.
- Compute mod = prefix % k.
- Increase answer by freq[mod] (how many times this mod was seen earlier).
- Increase freq[mod] by 1.

### Dry Run Example

nums = [4, 5, 0, -2, -3, 1], k = 5

We maintain freq array meaning:

freq[r] = number of prefix sums with remainder r.

We start with freq[0] = 1 because prefix before starting is 0 (divisible).

| Index | num | prefix | mod | freq before | add to total | freq after   | total so far |
| ----- | --- | ------ | --- | ----------- | ------------ | ------------ | ------------ |
| -     | -   | 0      | 0   | freq[0] = 1 | -            | freq = {0:1} | 0            |
| 0     | 4   | 4      | 4   | freq[4] = 0 | +0           | freq[4] = 1  | 0            |
| 1     | 5   | 9      | 4   | freq[4] = 1 | +1           | freq[4] = 2  | 1            |
| 2     | 0   | 9      | 4   | freq[4] = 2 | +2           | freq[4] = 3  | 3            |
| 3     | -2  | 7      | 2   | freq[2] = 0 | +0           | freq[2] = 1  | 3            |
| 4     | -3  | 4      | 4   | freq[4] = 3 | +3           | freq[4] = 4  | 6            |
| 5     | 1   | 5      | 0   | freq[0] = 1 | +1           | freq[0] = 2  | 7            |

Final answer = **7**

### Code

```cpp
int subarraysDivByK(vector<int>& nums, int k) {
    unordered_map<int,int> freq;
    freq[0] = 1;

    int prefix = 0;
    int count = 0;

    for(int x : nums) {
        prefix += x;

        int mod = ((prefix % k) + k) % k;

        if(freq.count(mod))
            count += freq[mod];

        freq[mod]++;
    }
    return count;
}
```

### Complexity Analysis

**Time Complexity:** `O(n)` – One pass with hashing.

**Space Complexity:** `O(k)` – Remainders range from 0 to k−1.

---

THE END
