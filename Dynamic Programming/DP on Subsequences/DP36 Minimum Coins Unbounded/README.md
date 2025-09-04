# Minimum Coins Unbounded

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

Given an array of coin denominations and a target value, find the minimum number of coins required to make the target (unlimited supply of each coin), or return `-1` if it is not possible. Note we can take any coin any number of times.

## Editorial

## Recursion

- At each coin index `i`, we have **two choices**:
  1. **Not take** the coin and move to the previous index.
  2. **Take** the coin (if denomination ≤ target) and stay at the same index (since unlimited supply is allowed).
- Base cases:
  - If `i == 0`, check if `target % arr[0] == 0`. If yes, return `target / arr[0]`, which tells the count, else return a very large value (`1e9`) to represent impossible.

### Code

```cpp
int f(int i, int target, vector<int>& arr) {
    if (i == 0) {
        if (target % arr[0] == 0) return target / arr[0];
        return 1e9;
    }

    int notTake = f(i - 1, target, arr);
    int take = 1e9;
    if (arr[i] <= target) {
        take = 1 + f(i, target - arr[i], arr);
    }

    return min(take, notTake);
}
```

### Complexity Analysis

**Time Complexity:** `O(2^n * target)` – At each step, we explore take/not-take paths.

**Space Complexity:** `O(n)` – Recursion stack depth.

---

## Memoization

- Use a DP table `dp[i][target]` to store minimum coins for subproblems.
- Before computing, check if the result already exists.
- Store results after computing.

### Code

```cpp
int f(int i, int target, vector<int>& arr, vector<vector<int>>& dp) {
    if (i == 0) {
        if (target % arr[0] == 0) return target / arr[0];
        return 1e9;
    }

    if (dp[i][target] != -1) return dp[i][target];

    int notTake = f(i - 1, target, arr, dp);
    int take = 1e9;
    if (arr[i] <= target) {
        take = 1 + f(i, target - arr[i], arr, dp);
    }

    return dp[i][target] = min(take, notTake);
}
```

### Complexity Analysis

**Time Complexity:** `O(n * target)` – Each state `(i, target)` computed once.

**Space Complexity:** `O(n * target)` (dp table) + `O(n)` recursion stack.

---

## Tabulation

- Convert recursion into bottom-up DP.
- Base case:
  - For `i = 0`, if `target % arr[0] == 0`, `dp[0][target] = target / arr[0]`, else `1e9`.
- Fill `dp[i][target]` for all coins and targets.

### Code

```cpp
int minimumCoins(vector<int>& arr, int T) {
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(T + 1, 0));

    for (int t = 0; t <= T; t++) {
        if (t % arr[0] == 0) dp[0][t] = t / arr[0];
        else dp[0][t] = 1e9;
    }

    for (int i = 1; i < n; i++) {
        for (int t = 0; t <= T; t++) {
            int notTake = dp[i - 1][t];
            int take = 1e9;
            if (arr[i] <= t) {
                take = 1 + dp[i][t - arr[i]];
            }
            dp[i][t] = min(take, notTake);
        }
    }

    int ans = dp[n - 1][T];
    return (ans >= 1e9 ? -1 : ans);
}
```

### Complexity Analysis

**Time Complexity:** `O(n * target)` – Filling DP table.

**Space Complexity:** `O(n * target)` – DP table storage.

---

## Space Optimization (Two Arrays)

- At step `i`, we only need values from row `i-1` and current row.
- Use two arrays: `prev` and `curr`.

### Code

```cpp
int minimumCoins(vector<int>& arr, int T) {
    int n = arr.size();
    vector<int> prev(T + 1, 0), curr(T + 1, 0);

    for (int t = 0; t <= T; t++) {
        if (t % arr[0] == 0) prev[t] = t / arr[0];
        else prev[t] = 1e9;
    }

    for (int i = 1; i < n; i++) {
        for (int t = 0; t <= T; t++) {
            int notTake = prev[t];
            int take = 1e9;
            if (arr[i] <= t) {
                take = 1 + curr[t - arr[i]];
            }
            curr[t] = min(take, notTake);
        }
        prev = curr;
    }

    int ans = prev[T];
    return (ans >= 1e9 ? -1 : ans);
}
```

### Complexity Analysis

**Time Complexity:** `O(n * target)` – Iterating over all states.

**Space Complexity:** `O(2 * target)` → simplified to `O(target)`.

---

## Space Optimization (Single Array)

- Observe: In the above two-array solution, for `take`, we use the **current row’s values** (since unlimited coins are allowed).
- Hence, we can reduce to **one array** updated in-place.

### Code

```cpp
int minimumCoins(vector<int>& arr, int T) {
    int n = arr.size();
    vector<int> dp(T + 1, 0);

    for (int t = 0; t <= T; t++) {
        if (t % arr[0] == 0) dp[t] = t / arr[0];
        else dp[t] = 1e9;
    }

    for (int i = 1; i < n; i++) {
        for (int t = 0; t <= T; t++) {
            int notTake = dp[t];
            int take = 1e9;
            if (arr[i] <= t) {
                take = 1 + dp[t - arr[i]];
            }
            dp[t] = min(take, notTake);
        }
    }

    int ans = dp[T];
    return (ans >= 1e9 ? -1 : ans);
}
```

### Complexity Analysis

**Time Complexity:** `O(n * target)` – Same as before.

**Space Complexity:** `O(target)` – Only one array maintained.

---

THE END
