# Minimum Subset Sum

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

Given a set of positive integers, partition it into two subsets such that the **absolute difference of their sums** is minimized, and return this minimum difference.

## Editorial

We need to recognize this as a **variation of** subset sum problem.

**Total sum idea**

Let `S = sum(arr)`. If we split into two subsets `S1` and `S2`, then:

- `S1 + S2 = S`
- Difference = `|S1 - S2| = |S - 2*S1|`.

So, minimizing the difference means finding a subset with sum `S1` **as close as possible to `S/2`**.

**DP transformation**

This reduces to:

- Can we form a subset with sum `j`? (`j` up to `S/2`).
- Use classic **subset-sum DP** to fill a boolean table.

**DP table**

- Define `dp[i][j] = true` if we can form sum `j` using first `i` elements.
- Transition:
  - If not taking element: `dp[i][j] = dp[i-1][j]`
  - If taking element: `dp[i][j] = dp[i-1][j-arr[i-1]]` (if `j >= arr[i-1]`).

**Result**

After filling the table, find the **largest `j <= S/2` where `dp[n][j]` is true**.

The answer is `S - 2*j`.

### Initial Code

This is the first code:

```cpp
int f(vector<int>& arr) {
    int n = arr.size();
    int total = accumulate(arr.begin(), arr.end(), 0);
    int half = total / 2;

    vector<bool> prev(half+1, false), cur(half+1, false);
    prev[0] = true;
    if (arr[0] <= half) prev[arr[0]] = true;

    for (int i = 1; i < n; i++) {
        cur[0] = true;
        for (int target = 1; target <= half; target++) {
            bool notTake = prev[target];
            bool take = false;
            if (arr[i] <= target) take = prev[target-arr[i]];
            cur[target] = take || notTake;
        }
        prev = cur;
    }

    int mini = INT_MAX;
    for (int s1 = 0; s1 <= half; s1++) {
        if (prev[s1]) {
            int diff = abs((total - s1) - s1);
            mini = min(mini, diff);
        }
    }
    return mini;
}
```

We can optimize this in many ways and write like a proper coding platforms template:

- **Use a single 1D array** instead of `prev` + `cur`.
  - Loop the `target` in **reverse order** to avoid overwriting needed values.
- This removes the need for `cur` entirely and reduces memory usage by half.
- Remove redundant `take`/`notTake` booleans inside the loop.
- Change the order of finding the min difference by running the loop from the end and break once found the first value.
- Use `long long` to avoid large values.

### Final Code

```cpp
int f(vector<int>& arr) {
    int n = arr.size();
    long long sum = accumulate(arr.begin(), arr.end(), 0LL);

    vector<bool> dp(sum/2 + 1, false);
    dp[0] = true;

    for(int num : arr) {
        for(long long j = sum/2; j >= num; j--) {
            dp[j] = dp[j] || dp[j - num];
        }
    }

    long long best = 0;
    for(long long j = sum/2; j >= 0; j--) {
        if(dp[j]) { best = j; break; }
    }
    return (int)(sum - 2*best);
}
```

### Complexity Analysis

**Time Complexity:** `O(n * sum)` – For each of `n` elements, we iterate over `sum/2` possible sums.

**Space Complexity:** `O(sum)` – We only keep one DP array of length `sum/2 + 1`.

---

THE END
