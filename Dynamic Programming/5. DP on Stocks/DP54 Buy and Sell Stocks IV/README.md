# Best Time to Buy and Sell Stock IV

Author: [Prakash JC](https://prakash079513.github.io/)

## Problem Statement

We are given an array `Arr[]` of length `n`, where each element represents the stock price on day `i`.

We are allowed to perform **at most k transactions** (1 transaction = 1 buy + 1 sell).

We must maximize the profit.

Rules:

- We cannot engage in multiple transactions simultaneously (must sell before buying again).
- At most `k` transactions are allowed.

---

## Editorial

### Recursion

- Define a function `f(i, t, buy)`:
  - `i`: current day (0 → n-1).
  - `t`: number of transactions left (max `k`).
  - `buy`: 1 if we can buy, 0 if we must sell.
- Choices:
  - If `buy == 1`:
    - Buy → `Arr[i] + f(i+1, t, 0)`
    - Skip → `f(i+1, t, 1)`
  - If `buy == 0`:
    - Sell → `Arr[i] + f(i+1, t-1, 1)`
    - Skip → `f(i+1, t, 0)`
- Base case: if `i == n` or `t == 0`, return `0`.

### Code

```cpp
int f(int i, int t, int buy, vector<int>& arr, int n) {
    if (i == n || t == 0) return 0;

    if (buy) {
        int take = -arr[i] + f(i + 1, t, 0, arr, n);
        int notTake = f(i + 1, t, 1, arr, n);
        return max(take, notTake);
    } else {
        int sell = arr[i] + f(i + 1, t - 1, 1, arr, n);
        int notSell = f(i + 1, t, 0, arr, n);
        return max(sell, notSell);
    }
}
```

### Complexity Analysis

**Time Complexity:** `O(2^n)` – Exponential, every day has two choices.

**Space Complexity:** `O(n)` – Recursion stack depth.

---

## Memoization

- Use a 3D DP table `dp[i][t][buy]`.
- Before computing, check if already stored.

### Code

```cpp
int f(int i, int t, int buy, vector<int>& arr, int n, vector<vector<vector<int>>>& dp) {
    if (i == n || t == 0) return 0;
    if (dp[i][t][buy] != -1) return dp[i][t][buy];

    if (buy) {
        int take = -arr[i] + f(i + 1, t, 0, arr, n, dp);
        int notTake = f(i + 1, t, 1, arr, n, dp);
        return dp[i][t][buy] = max(take, notTake);
    } else {
        int sell = arr[i] + f(i + 1, t - 1, 1, arr, n, dp);
        int notSell = f(i + 1, t, 0, arr, n, dp);
        return dp[i][t][buy] = max(sell, notSell);
    }
}
```

### Complexity Analysis

**Time Complexity:** `O(n * k * 2)` = `O(n * k)`.

**Space Complexity:** `O(n * k * 2)` for dp + `O(n)` recursion stack.

---

## Tabulation

- Bottom-up DP: `dp[n+1][k+1][2]`.
- Base: `dp[n][t][buy] = 0` for all states.
- Fill from `i = n-1` down to `0`.

### Code

```cpp
int f(vector<int>& arr, int K) {
    int n = arr.size();
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(K + 1, vector<int>(2, 0)));

    for (int i = n - 1; i >= 0; i--) {
        for (int t = 1; t <= K; t++) {
            dp[i][t][1] = max(-arr[i] + dp[i + 1][t][0], dp[i + 1][t][1]);
            dp[i][t][0] = max(arr[i] + dp[i + 1][t - 1][1], dp[i + 1][t][0]);
        }
    }
    return dp[0][K][1];
}
```

### Complexity Analysis

**Time Complexity:** `O(n * k)` – Filling all states.

**Space Complexity:** `O(n * k * 2)`.

---

## Space Optimization

- Only `ahead[t][buy]` (for day `i+1`) and `curr[t][buy]` (for day `i`) are needed.
- Reduce to 2D arrays.

### Code

```cpp
int f(vector<int>& arr, int K) {
    int n = arr.size();
    vector<vector<int>> ahead(K + 1, vector<int>(2, 0)), curr(K + 1, vector<int>(2, 0));

    for (int i = n - 1; i >= 0; i--) {
        for (int t = 1; t <= K; t++) {
            curr[t][1] = max(-arr[i] + ahead[t][0], ahead[t][1]);
            curr[t][0] = max(arr[i] + ahead[t - 1][1], ahead[t][0]);
        }
        ahead = curr;
    }
    return ahead[K][1];
}
```

### Complexity Analysis

**Time Complexity:** `O(n * k)` – Iterating days × transactions.

**Space Complexity:** `O(k * 2)` → simplified to `O(k)`.

---

THE END
