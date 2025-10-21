# **3346. Maximum Frequency of an Element After Performing Operations I**

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

[Link](https://leetcode.com/problems/maximum-frequency-of-an-element-after-performing-operations-i/description/)

You are given an integer array `nums` and two integers `k` and `numOperations`.

You must perform an operation `numOperations` times on `nums`, where in each operation you:

1. Select an index `i` that was not selected in any previous operations.
2. Add an integer in the range `[-k, k]` to `nums[i]`.

Return the **maximum possible frequency** of any element in `nums` after performing the operations.

---

**Example 1:**

Input: `nums = [1,4,5]`, `k = 1`, `numOperations = 2`

Output: `2`

**Explanation:**

We can achieve a maximum frequency of two by:

- Adding 0 to `nums[1]` → `nums = [1, 4, 5]`
- Adding -1 to `nums[2]` → `nums = [1, 4, 4]`

---

**Example 2:**

Input: `nums = [5,11,20,20]`, `k = 5`, `numOperations = 1`

Output: `2`

**Explanation:**

We can achieve a maximum frequency of two by:

- Adding 0 to `nums[1]`.

---

**Constraints:**

- `1 <= nums.length <= 10⁵`
- `1 <= nums[i] <= 10⁵`
- `0 <= k <= 10⁵`
- `0 <= numOperations <= nums.length`

---

## Editorial

## **Approach 1: Sort + Enumerate + Binary Search**

### **Intuition**

- You are allowed to perform up to `numOperations` changes, where each change can adjust an element by at most `k` units (either +k or -k).
- The goal is to find the **maximum frequency** of any integer that can be obtained after these operations.
- This means: choose a **target number** `m` and see how many elements can be shifted (within ±k) to become `m`.

---

### **Step-by-Step Reasoning**

### **1. Handle the Operations Constraint**

- The problem says you must perform exactly `numOperations` operations.
- However, since we can “add 0” (meaning no change), the effective rule is **you can adjust up to `numOperations` elements** within the range `[−k, +k]`.

### **2. Sort the Array**

- Sorting simplifies range queries — all numbers close to each other are grouped together.
- This allows binary search to efficiently find which elements can be moved to a given target value.

### **3. Enumerate Every Possible Target Value**

- Let’s assume the smallest number is `num_min` and largest is `num_max`.
- Then every possible target number lies in `[num_min, num_max]`.
- For each target `m`, we’ll calculate how many numbers in `nums` can be converted to `m`.

### **4. Use Binary Search to Find the Convertible Range**

- For each `m`, numbers that can become `m` must lie within `[m−k, m+k]`.
- We use **binary search** to find:
  - `l =` index of the first element ≥ `m−k` (`leftBound`)
  - `r =` index of the last element ≤ `m+k` (`rightBound`)
- So all numbers in indices `[l, r]` can be changed to `m`.

### **5. Calculate Frequency for Each Target**

- The number of convertible elements is `(r − l + 1)`.
- But you can only modify up to `numOperations` elements.
- If the target `m` already exists in `nums`, say it occurs `count_m` times, then:
  - You can keep those `count_m` elements as they are.
  - You can use your remaining operations to convert nearby elements to `m`.
- So the frequency for this target is:
  **`f_m = min(r − l + 1, numOperations + count_m)`**

### **6. Track the Global Maximum**

- Keep updating the maximum frequency `ans` across all possible target values.

---

### **Code**

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        sort(nums.begin(), nums.end());
        int ans = 0;
        unordered_map<int, int> numCount;

        // Step 1: Count occurrences of each number
        int lastNumIndex = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != nums[lastNumIndex]) {
                numCount[nums[lastNumIndex]] = i - lastNumIndex;
                ans = max(ans, i - lastNumIndex);
                lastNumIndex = i;
            }
        }
        numCount[nums[lastNumIndex]] = nums.size() - lastNumIndex;
        ans = max(ans, (int)nums.size() - lastNumIndex);

        // Step 2: Define left and right bound search
        auto leftBound = [&](int value) {
            int left = 0, right = nums.size() - 1;
            while (left < right) {
                int mid = (left + right) / 2;
                if (nums[mid] < value) left = mid + 1;
                else right = mid;
            }
            return left;
        };

        auto rightBound = [&](int value) {
            int left = 0, right = nums.size() - 1;
            while (left < right) {
                int mid = (left + right + 1) / 2;
                if (nums[mid] > value) right = mid - 1;
                else left = mid;
            }
            return left;
        };

        // Step 3: Enumerate each target value
        for (int m = nums.front(); m <= nums.back(); ++m) {
            int l = leftBound(m - k);
            int r = rightBound(m + k);

            int tempFreq;
            if (numCount.count(m))
                tempFreq = min(r - l + 1, numCount[m] + numOperations);
            else
                tempFreq = min(r - l + 1, numOperations);

            ans = max(ans, tempFreq);
        }
        return ans;
    }
};
```

### **Complexity Analysis**

**Time Complexity:** `O(n log n + R log n)`

- `O(n log n)` for sorting.
- `O(R log n)` for enumerating each possible target value and performing two binary searches per target, where `R = num_max − num_min + 1`.

**Space Complexity:** `O(n)`

- For storing the frequency map and the input array.

---

### **Summary**

- The key trick: **Enumerate each target and use binary search on the sorted array** to find the range of elements convertible to that target within `k`.
- Combine the count of existing occurrences with the available operations to compute the maximum possible frequency.
- Elegant because it avoids brute-force pair comparisons, instead leveraging sorting and binary bounds efficiently.

---

## Approach 2: Using Prefix Sum

### **Intuition**

We are allowed to perform at most `numOperations` changes, where each change can add any integer in the range `[-k, k]` to a _different_ element.

Our goal is to make as many elements as possible equal to a common value.

Instead of directly changing the numbers, we think **in terms of possible target values**:

For each potential target value x, how many numbers can we convert to x using the allowed operations?

A number `num` can be converted to `x` if:

```
|num - x| ≤ k
```

That means all numbers lying within the range `[x - k, x + k]` can potentially become `x`.

So for each possible `x`, we want to know:

- How many numbers already equal `x`
- How many _nearby numbers_ (within ±k) can be turned into `x`
- But we can only use `numOperations` of them.

Hence, we need to efficiently count how many numbers lie inside `[x - k, x + k]` for every `x`.

---

### **Approach**

### Step 1: Frequency Array

We first count how many times each integer appears:

```cpp
for (int num : nums)
    freq[num]++;
```

This helps us know exactly how many occurrences of each number exist.

---

### Step 2: Prefix Sum Array (Actually Prefix Count)

We construct a prefix sum array such that: For all i from `0` to `n` .

```
n = maxVal + k + 2
```

gives enough buffer so that our prefix sum and frequency arrays can safely handle all possible indices we might query.

```
prefixSum[i] = total count of numbers ≤ i
```

This allows us to instantly find how many numbers lie within any range `[L, R]`:

```
count = prefixSum[R] - prefixSum[L - 1]
```

### **Dry Run**

**Example:** `nums = [1, 4, 5], k = 1, operations = 2`

| Value | freq | prefixSum |
| ----- | ---- | --------- |
| 0     | 0    | 0         |
| 1     | 1    | 1         |
| 2     | 0    | 1         |
| 3     | 0    | 1         |
| 4     | 1    | 2         |
| 5     | 1    | 3         |
| 6     | 0    | 3         |

### Example:

Find how many numbers lie between `[3, 5]`

- prefixSum[5] = 3 → numbers ≤ 5 = (1, 4, 5)
- prefixSum[2] = 1 → numbers ≤ 2 = (1)
- So between 3 and 5:
  `prefixSum[5] - prefixSum[2] = 3 - 1 = 2`

Two numbers in `[3, 5]` — indeed, they are `4` and `5`.

So, for a target `x`, we can get the total count of numbers within `[x - k, x + k]` in O(1).

---

### Step 3: Try Each Target

For every target `x` (from 0 to max number in nums):

1. Compute `L = max(0, x - k)` and `R = min(maxIndex, x + k)`
2. Count how many numbers lie in `[L, R]`
3. Exclude the ones already equal to `x` (since we don’t need to change them)
4. Add up to `numOperations` more from nearby numbers that can be changed
5. Track the best (maximum) frequency possible

Formula:

```
totalCount = prefixSum[R] - prefixSum[L - 1]
canChange = totalCount - freq[x]
possibleFreq = freq[x] + min(numOperations, canChange)
```

Dry run:

| Target | Range | totalCount | freq[target] | canChange | possibleFreq |
| ------ | ----- | ---------- | ------------ | --------- | ------------ |
| 1      | [0,2] | 1          | 1            | 0         | 1            |
| 4      | [3,5] | 2          | 1            | 1         | 2            |
| 5      | [4,6] | 2          | 1            | 1         | 2            |

---

### **Code**

```cpp
int maxFrequency(vector<int>& nums, int k, int operations) {
    int maxVal = *max_element(nums.begin(), nums.end());
    int n = maxVal + k + 2;

    // Step 1: Frequency array
    vector<int> freq(n, 0);
    for (int num : nums) freq[num]++;

    // Step 2: Prefix sum array
    vector<int> prefixSum(n, 0);
    prefixSum[0] = freq[0];
    for (int i = 1; i < n; i++)
        prefixSum[i] = prefixSum[i - 1] + freq[i];

    // Step 3: Try each possible target
    int maxFreq = 0;
    for (int target = 0; target <= maxVal; target++) {
        int left = max(0, target - k);
        int right = min(n - 1, target + k);

        int totalCount = prefixSum[right] - (left > 0 ? prefixSum[left - 1] : 0);
        int canChange = totalCount - freq[target];
        int possibleFreq = freq[target] + min(operations, canChange);

        maxFreq = max(maxFreq, possibleFreq);
    }

    return maxFreq;
}
```

---

### **Complexity Analysis**

**Time Complexity:** `O(maxVal)`

We iterate through all possible target values up to the maximum element, doing only O(1) work per target.

**Space Complexity:** `O(maxVal + k)`

We store two arrays — `freq` and `prefixSum` — up to index `maxVal + k`.

---

### **Key Takeaways**

- The prefix sum trick converts an `O(n²)` range-counting process into `O(n)`.
- By precomputing frequencies, we avoid checking every number repeatedly.
- The logic is effectively a **range counting + limited operation adjustment** problem.

This makes it a clean **prefix-sum-based counting approach**, far simpler than the sliding window or two-pointer variant often used for similar problems.

## Optimized code

```cpp
#include <algorithm>
#include <span>
#include <vector>

#ifdef __GNUC__
#define FORCE_INLINE inline __attribute__((always_inline))
#else
#define FORCE_INLINE inline
#endif

template <typename To, typename From, std::size_t extent = std::dynamic_extent>
    requires(sizeof(To) == sizeof(From))
[[nodiscard]] FORCE_INLINE static auto reinterpret_range(
    std::span<From, extent> in) noexcept
{
    return std::span<To, extent>{
        reinterpret_cast<To*>(in.data()),  // NOLINT
        in.size()};
}

template <typename To, typename From, typename Allocator>
    requires(sizeof(To) == sizeof(From))
[[nodiscard]] FORCE_INLINE static std::span<To> reinterpret_range(
    std::vector<From, Allocator>& v) noexcept
{
    return reinterpret_range<To>(std::span{v});
}

class Solution
{
public:
    using u32 = uint32_t;
    inline static std::array<u32, 200'005> freq;
    inline static std::array<u32, 200'005> prefixSum;

    [[nodiscard]] static constexpr u32 maxFrequency(
        std::vector<int>& _nums,
        const u32 k,
        const u32 operations) noexcept
    {
        std::span<u32> nums = reinterpret_range<u32>(_nums);

        u32 maxVal = *std::ranges::max_element(nums);
        u32 n = maxVal + k + 2;
        std::ranges::fill_n(freq.begin(), n, u32{});
        for (auto num : nums) ++freq[num];

        if (auto it = freq.begin(); operations == 0)
        {
            return *std::max_element(it, std::next(it, n));
        }

        prefixSum[n] = 0;
        prefixSum[0] = freq[0];
        for (u32 i = 1; i < n; ++i) prefixSum[i] = prefixSum[i - 1] + freq[i];

        u32 maxFreq = 0;
        for (u32 target = 0; target <= maxVal; ++target)
        {
            u32 left = target > k ? target - k : n + 1;
            u32 right = std::min(n - 1, target + k);
            u32 totalCount = prefixSum[right] - prefixSum[left - 1];
            u32 canChange = totalCount - freq[target];
            u32 possibleFreq = freq[target] + std::min(operations, canChange);
            maxFreq = std::max(maxFreq, possibleFreq);
        }

        return maxFreq;
    }
};
```

---

THE END
