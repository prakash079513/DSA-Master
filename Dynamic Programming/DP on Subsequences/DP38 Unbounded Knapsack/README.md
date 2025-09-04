# Unbounded Knapsack

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

Given `n` items with weights `wt[i]` and values `val[i]`, and a knapsack of capacity `W`, determine the **maximum total value** you can obtain. You can take **any item any number of times** (unbounded supply).

## Editorial

## Recursion

- At each item index `i`, we have **two choices**:
  1. **Not take** the item → move to the previous index.
  2. **Take** the item (if weight ≤ capacity) → stay at the same index and reduce the remaining capacity.
- Base case:
  - If `i == 0`, the only option is to take as many items of type `0` as possible, i.e., `val[0] * (W / wt[0])`.

### Code

```cpp
int f(int i, int W, vector<int>& wt, vector<int>& val) {
    if (i == 0) {
        return (W / wt[0]) * val[0];
    }

    int notTake = f(i - 1, W, wt, val);
    int take = 0;
    if (wt[i] <= W) {
        take = val[i] + f(i, W - wt[i], wt, val);
    }

    return max(take, notTake);
}

```

### Complexity Analysis

**Time Complexity:** `O(2^n * W)` – Exploring both choices repeatedly.

**Space Complexity:** `O(n)` – Recursion stack depth.

---

## Memoization

- Use a DP table `dp[i][W]` that stores the maximum value for capacity `W` using items up to index `i`.
- Before computing, check if it’s already stored.

### Code

```cpp
int f(int i, int W, vector<int>& wt, vector<int>& val, vector<vector<int>>& dp) {
    if (i == 0) {
        return (W / wt[0]) * val[0];
    }

    if (dp[i][W] != -1) return dp[i][W];

    int notTake = f(i - 1, W, wt, val, dp);
    int take = 0;
    if (wt[i] <= W) {
        take = val[i] + f(i, W - wt[i], wt, val, dp);
    }

    return dp[i][W] = max(take, notTake);
}
```

### Complexity Analysis

**Time Complexity:** `O(n * W)` – Each `(i, W)` computed once.

**Space Complexity:** `O(n * W)` (DP table) + `O(n)` recursion stack.

---

## Tabulation

- Build a 2D DP table.
- Base case:
  - For `i = 0`, `dp[0][w] = (w / wt[0]) * val[0]`.
- Transition:
  - `dp[i][w] = max(dp[i-1][w], val[i] + dp[i][w - wt[i]])`.

### Code

```cpp
int unboundedKnapsack(int n, int W, vector<int>& wt, vector<int>& val) {
    vector<vector<int>> dp(n, vector<int>(W + 1, 0));

    for (int w = 0; w <= W; w++) {
        dp[0][w] = (w / wt[0]) * val[0];
    }

    for (int i = 1; i < n; i++) {
        for (int w = 0; w <= W; w++) {
            int notTake = dp[i - 1][w];
            int take = 0;
            if (wt[i] <= w) {
                take = val[i] + dp[i][w - wt[i]];
            }
            dp[i][w] = max(take, notTake);
        }
    }

    return dp[n - 1][W];
}
```

### Complexity Analysis

**Time Complexity:** `O(n * W)` – Filling DP table.

**Space Complexity:** `O(n * W)` – Full DP storage.

---

## Space Optimization (Two Arrays)

- At each step, we only need the previous row (`prev`) and current row (`curr`).
- Transition remains the same.

### Code

```cpp
int unboundedKnapsack(int n, int W, vector<int>& wt, vector<int>& val) {
    vector<int> prev(W + 1, 0), curr(W + 1, 0);

    for (int w = 0; w <= W; w++) {
        prev[w] = (w / wt[0]) * val[0];
    }

    for (int i = 1; i < n; i++) {
        for (int w = 0; w <= W; w++) {
            int notTake = prev[w];
            int take = 0;
            if (wt[i] <= w) {
                take = val[i] + curr[w - wt[i]];
            }
            curr[w] = max(take, notTake);
        }
        prev = curr;
    }

    return prev[W];
}
```

### Complexity Analysis

**Time Complexity:** `O(n * W)` – Iterating all states.

**Space Complexity:** `O(2 * W)` → simplified to `O(W)`.

---

## Space Optimization (Single Array)

- Since the `take` transition uses the **current row**, we can optimize further to a **single array**.
- Iterate `w` from `0 → W`.

### Code

```cpp
int unboundedKnapsack(int n, int W, vector<int>& wt, vector<int>& val) {
    vector<int> dp(W + 1, 0);

    for (int w = 0; w <= W; w++) {
        dp[w] = (w / wt[0]) * val[0];
    }

    for (int i = 1; i < n; i++) {
        for (int w = 0; w <= W; w++) {
            int notTake = dp[w];
            int take = 0;
            if (wt[i] <= w) {
                take = val[i] + dp[w - wt[i]];
            }
            dp[w] = max(take, notTake);
        }
    }

    return dp[W];
}
```

### Complexity Analysis

**Time Complexity:** `O(n * W)` – Same transitions.

**Space Complexity:** `O(W)` – Only one array used.

---

THE END
