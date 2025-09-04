# Coin Change Unbounded

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

Given an array of coin denominations and a target value, count the **total number of distinct ways** to make the target using unlimited supply of each coin.

---

## Editorial

## Recursion

- At each coin index `i`, we have **two choices**:
  1. **Not take** the coin → move to the previous index.
  2. **Take** the coin → stay at the same index (since unlimited coins allowed) and reduce the target.
- Base cases:
  - If `i == 0`, check if `target % arr[0] == 0`. If yes, there is **1 way**, else **0 ways**.

### Code

```cpp
int f(int i, int target, vector<int>& arr) {
    if (i == 0) {
        return (target % arr[0] == 0);
    }

    int notTake = f(i - 1, target, arr);
    int take = 0;
    if (arr[i] <= target) {
        take = f(i, target - arr[i], arr);
    }

    return take + notTake;
}

```

### Complexity Analysis

**Time Complexity:** `O(2^n * target)` – Each state explored via take/not-take.

**Space Complexity:** `O(n)` – Recursion stack depth.

---

## Memoization

- Store results in a DP table `dp[i][target]` → number of ways to form `target` using coins up to index `i`.
- Return already computed value if present.

### Code

```cpp
int f(int i, int target, vector<int>& arr, vector<vector<int>>& dp) {
    if (i == 0) {
        return (target % arr[0] == 0);
    }

    if (dp[i][target] != -1) return dp[i][target];

    int notTake = f(i - 1, target, arr, dp);
    int take = 0;
    if (arr[i] <= target) {
        take = f(i, target - arr[i], arr, dp);
    }

    return dp[i][target] = take + notTake;
}
```

### Complexity Analysis

**Time Complexity:** `O(n * target)` – Each `(i, target)` computed once.

**Space Complexity:** `O(n * target)` (dp table) + `O(n)` recursion stack.

---

## Tabulation

- Bottom-up filling of DP table.
- Base case:
  - For `i = 0`, `dp[0][t] = 1` if `t % arr[0] == 0`, else `0`.
- Transition:
  - `dp[i][t] = dp[i-1][t] + dp[i][t - arr[i]]` (not take + take).

### Code

```cpp
int coinChangeWays(vector<int>& arr, int T) {
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(T + 1, 0));

    for (int t = 0; t <= T; t++) {
        dp[0][t] = (t % arr[0] == 0);
    }

    for (int i = 1; i < n; i++) {
        for (int t = 0; t <= T; t++) {
            int notTake = dp[i - 1][t];
            int take = 0;
            if (arr[i] <= t) {
                take = dp[i][t - arr[i]];
            }
            dp[i][t] = take + notTake;
        }
    }

    return dp[n - 1][T];
}
```

### Complexity Analysis

**Time Complexity:** `O(n * target)` – Filling DP table.

**Space Complexity:** `O(n * target)` – 2D DP storage.

---

## Space Optimization (Two Arrays)

- At step `i`, only the previous row (`prev`) and current row (`curr`) are needed.
- Transition remains the same.

### Code

```cpp
int coinChangeWays(vector<int>& arr, int T) {
    int n = arr.size();
    vector<int> prev(T + 1, 0), curr(T + 1, 0);

    for (int t = 0; t <= T; t++) {
        prev[t] = (t % arr[0] == 0);
    }

    for (int i = 1; i < n; i++) {
        for (int t = 0; t <= T; t++) {
            int notTake = prev[t];
            int take = 0;
            if (arr[i] <= t) {
                take = curr[t - arr[i]];
            }
            curr[t] = take + notTake;
        }
        prev = curr;
    }

    return prev[T];
}
```

### Complexity Analysis

**Time Complexity:** `O(n * target)` – Iterating all states.

**Space Complexity:** `O(2 * target)` → simplified to `O(target)`.

---

## Space Optimization (Single Array)

- Since `take` uses current row values, we can directly update a **single array**.
- Iterate `t` from `arr[i]` to `T` to avoid overwriting needed values.

### Code

```cpp
int coinChangeWays(vector<int>& arr, int T) {
    int n = arr.size();
    vector<int> dp(T + 1, 0);

    for (int t = 0; t <= T; t++) {
        dp[t] = (t % arr[0] == 0);
    }

    for (int i = 1; i < n; i++) {
        for (int t = arr[i]; t <= T; t++) {
            dp[t] += dp[t - arr[i]];
        }
    }

    return dp[T];
}
```

### Complexity Analysis

**Time Complexity:** `O(n * target)` – Same transitions.

**Space Complexity:** `O(target)` – Only one array used.

---

THE END
