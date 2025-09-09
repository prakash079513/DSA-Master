# Count Subsets with Sum K

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

Given an array with N positive integers and an integer K. Find the number of subsets whose sum is equal to K.

## Editorial

### Recursion

- At each index `i`, we have **two choices**:
  1. **Pick** the current element (if it does not exceed the remaining target).
  2. **Not pick** the current element.
- Recurse on the next index with updated target.
- Base cases:
  - If `target == 0`, we found one valid subset → return `1`.
  - If `i == 0`, check if `arr[0] == target`; return `1` if true, else `0`.

### Code

```cpp
int f(int i, int target, vector<int>& arr) {
    if (target == 0) return 1;
    if (i == 0) return (arr[0] == target);

    int notPick = f(i - 1, target, arr);

    int pick = 0;
    if (arr[i] <= target) {
        pick = f(i - 1, target - arr[i], arr);
    }

    return pick + notPick;
}
```

### Complexity Analysis

**Time Complexity:** `O(2^n)` – Every element has two choices (pick / not pick).

**Space Complexity:** `O(n)` – Due to recursion stack depth.

---

## Memoization

- Before computing, check if it’s already stored.
- Store the results.

### Code

```cpp
int f(int i, int target, vector<int>& arr, vector<vector<int>>& dp) {
    if (target == 0) return 1;
    if (i == 0) return (arr[0] == target);

    if (dp[i][target] != -1) return dp[i][target];

    int notPick = f(i - 1, target, arr, dp);
    int pick = 0;
    if (arr[i] <= target) {
        pick = f(i - 1, target - arr[i], arr, dp);
    }
    return dp[i][target] = pick + notPick;
}
```

### Complexity Analysis

**Time Complexity:** `O(n * k)` – Every state `(i, target)` computed once.

**Space Complexity:** `O(n * k)` (dp table) + `O(n)` recursion stack.

---

## Tabulation

Base cases:

- `dp[i][0] = 1` (empty subset always possible).
- `dp[0][arr[0]] = 1` (only if arr[0] ≤ k).

### Code

```cpp
int f(vector<int>& arr, int k) {
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(k + 1, 0));

    for (int i = 0; i < n; i++) dp[i][0] = 1;
    if (arr[0] <= k) dp[0][arr[0]] = 1;

    for (int i = 1; i < n; i++) {
        for (int target = 0; target <= k; target++) {
            int notPick = dp[i - 1][target];
            int pick = 0;
            if (arr[i] <= target) {
                pick = dp[i - 1][target - arr[i]];
            }
            dp[i][target] = pick + notPick;
        }
    }
    return dp[n - 1][k];
}
```

### Complexity Analysis

**Time Complexity:** `O(n * k)` – We compute for all states.

**Space Complexity:** `O(n * k)` – DP table storage.

---

## Space Optimization

- At step `i`, we only need values from `i-1`.
- Use two arrays: `prev` and `curr`.
- Update `curr` for each target, then assign `prev = curr`.

### Code

```cpp
int f(vector<int>& arr, int k) {
    int n = arr.size();
    vector<int> prev(k + 1, 0), curr(k + 1, 0);

    prev[0] = curr[0] = 1;
    if (arr[0] <= k) prev[arr[0]] = 1;

    for (int i = 1; i < n; i++) {
        for (int target = 0; target <= k; target++) {
            int notPick = prev[target];
            int pick = 0;
            if (arr[i] <= target) {
                pick = prev[target - arr[i]];
            }
            curr[target] = pick + notPick;
        }
        prev = curr;
    }
    return prev[k];
}
```

### Complexity Analysis

**Time Complexity:** `O(n * k)` – Same number of states.

**Space Complexity:** `O(k)` – Only two 1D arrays used.

---

THE END
