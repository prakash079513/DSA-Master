# 0/1 Knapsack Problem

Author: [Prakash JC](https://prakash079513.github.io)

## **Problem Statement**

You are given `n` items with weights `wt[i]` and values `val[i]`. You have a knapsack with maximum capacity `W`. You must pick a subset of items such that their total weight does not exceed `W` and their total value is maximized. Each item can be chosen at most once.

## Editorial

## Recursion

- At each item index `i`, you have **two choices**:
  1. **Not take** the item → move to `i-1` with the same `W`.
  2. **Take** the item (only if `wt[i] <= W`) → move to `i-1` with reduced capacity `W - wt[i]`, add its value.
- The answer is the maximum of the two choices.
- **Base case:** If `i == 0`, return `val[0]` if `wt[0] <= W`, else return `0`.

### Code

```cpp
int f(int i, int W, vector<int>& wt, vector<int>& val) {
    if (i == 0) {
        if (wt[0] <= W) return val[0];
        return 0;
    }
    int notTake = f(i - 1, W, wt, val);
    int take = INT_MIN;
    if (wt[i] <= W) take = val[i] + f(i - 1, W - wt[i], wt, val);
    return max(notTake, take);
}
```

### Complexity Analysis

**Time Complexity:** `O(2^n)` – Each item has 2 choices (take/not take).

**Space Complexity:** `O(n)` – Recursion depth.

---

## Memoization

- Store results in a DP table `dp[i][W]` where:
  `dp[i][W] = max value achievable using items [0..i] with capacity W`.
- If already computed, return stored value.

### Code

```cpp
int f(int i, int W, vector<int>& wt, vector<int>& val, vector<vector<int>>& dp) {
    if (i == 0) {
        if (wt[0] <= W) return val[0];
        return 0;
    }
    if (dp[i][W] != -1) return dp[i][W];
    int notTake = f(i - 1, W, wt, val, dp);
    int take = INT_MIN;
    if (wt[i] <= W) take = val[i] + f(i - 1, W - wt[i], wt, val, dp);
    return dp[i][W] = max(notTake, take);
}
```

### Complexity Analysis

**Time Complexity:** `O(n*W)` – Each state `(i, W)` computed once.

**Space Complexity:** `O(n*W)` for DP table + `O(n)` recursion stack.

---

## Tabulation

- Iterative DP using `dp[n][W+1]`.
- Base initialization: If `wt[0] <= W`, `dp[0][w] = val[0]` for all `w >= wt[0]`.
- Transition:
  `dp[i][w] = max(dp[i-1][w], val[i] + dp[i-1][w - wt[i]]) if wt[i] <= w`.
  Else `dp[i][w] = dp[i-1][w]`.

### Code

```cpp
int f(vector<int>& wt, vector<int>& val, int W) {
    int n = wt.size();
    vector<vector<int>> dp(n, vector<int>(W + 1, 0));

    for (int w = wt[0]; w <= W; w++) dp[0][w] = val[0];

    for (int i = 1; i < n; i++) {
        for (int w = 0; w <= W; w++) {
            int notTake = dp[i - 1][w];
            int take = INT_MIN;
            if (wt[i] <= w) take = val[i] + dp[i - 1][w - wt[i]];
            dp[i][w] = max(notTake, take);
        }
    }
    return dp[n - 1][W];
}
```

### Complexity Analysis

**Time Complexity:** `O(n*W)` – Filling `n*W` DP states.

**Space Complexity:** `O(n*W)` – Full DP table.

---

## Space Optimization (2 Arrays)

- Only `dp[i-1][*]` (previous row) is required at each step.
- Use two 1D arrays: `prev` and `cur`.

### Code

```cpp
int f(vector<int>& wt, vector<int>& val, int W) {
    int n = wt.size();
    vector<int> prev(W + 1, 0), cur(W + 1, 0);

    for (int w = wt[0]; w <= W; w++) prev[w] = val[0];

    for (int i = 1; i < n; i++) {
        for (int w = 0; w <= W; w++) {
            int notTake = prev[w];
            int take = INT_MIN;
            if (wt[i] <= w) take = val[i] + prev[w - wt[i]];
            cur[w] = max(notTake, take);
        }
        prev = cur;
    }
    return prev[W];
}
```

### Complexity Analysis

**Time Complexity:** `O(n*W)` – Iterates through all states.

**Space Complexity:** `O(2*W)` → `O(W)` – Two 1D arrays.

---

## Space Optimization (1 Array)

- Use **only one array**.
- Update in reverse (`w = W → wt[i]`) to prevent overwriting required states.

### Code

```cpp
int f(vector<int>& wt, vector<int>& val, int W) {
    int n = wt.size();
    vector<int> dp(W + 1, 0);

    for (int w = wt[0]; w <= W; w++) dp[w] = val[0];

    for (int i = 1; i < n; i++) {
        for (int w = W; w >= 0; w--) {
            if (wt[i] <= w)
                dp[w] = max(dp[w], val[i] + dp[w - wt[i]]);
        }
    }
    return dp[W];
}
```

### Complexity Analysis

**Time Complexity:** `O(n*W)` – Each item iterates over capacity.

**Space Complexity:** `O(W)` – Only one DP array.

---

THE END
