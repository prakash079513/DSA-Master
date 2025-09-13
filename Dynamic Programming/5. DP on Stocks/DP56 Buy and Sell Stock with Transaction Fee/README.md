# Best Time to Buy and Sell Stock with Transaction Fee

Author: [Prakash JC](https://prakash079513.github.io/)

## Problem Statement

We are given an array `Arr[]` of length `n`, where `Arr[i]` represents the stock price on day `i`.

We can perform unlimited transactions, but **each sell transaction costs a fee** (given as `fee`).

We must maximize the profit after accounting for transaction fees.

---

## Editorial

### Recursion

- Define `f(i, buy)`:
  - `i`: current day.
  - `buy`: 1 if we can buy, 0 if we must sell.
- Choices:
  - If `buy == 1`:
    - Buy → `Arr[i] + f(i+1, 0)`
    - Skip → `f(i+1, 1)`
  - If `buy == 0`:
    - Sell → `Arr[i] - fee + f(i+1, 1)` (subtract transaction fee)
    - Skip → `f(i+1, 0)`
- Base case: if `i == n`, return `0`.

### Code

```cpp
int f(int i, int buy, vector<int>& arr, int n, int fee) {
    if (i == n) return 0;

    if (buy) {
        int take = -arr[i] + f(i + 1, 0, arr, n, fee);
        int notTake = f(i + 1, 1, arr, n, fee);
        return max(take, notTake);
    } else {
        int sell = arr[i] - fee + f(i + 1, 1, arr, n, fee);
        int notSell = f(i + 1, 0, arr, n, fee);
        return max(sell, notSell);
    }
}
```

### Complexity Analysis

**Time Complexity:** `O(2^n)` – Two choices per day.

**Space Complexity:** `O(n)` – Recursion stack.

---

## Memoization

- Use `dp[i][buy]` to store computed results.

### Code

```cpp
int f(int i, int buy, vector<int>& arr, int n, int fee, vector<vector<int>>& dp) {
    if (i == n) return 0;
    if (dp[i][buy] != -1) return dp[i][buy];

    if (buy) {
        int take = -arr[i] + f(i + 1, 0, arr, n, fee, dp);
        int notTake = f(i + 1, 1, arr, n, fee, dp);
        return dp[i][buy] = max(take, notTake);
    } else {
        int sell = arr[i] - fee + f(i + 1, 1, arr, n, fee, dp);
        int notSell = f(i + 1, 0, arr, n, fee, dp);
        return dp[i][buy] = max(sell, notSell);
    }
}
```

### Complexity Analysis

**Time Complexity:** `O(n * 2)` = `O(n)`.

**Space Complexity:** `O(n * 2)` for dp + `O(n)` recursion stack.

---

## Tabulation

- Build `dp[n+1][2]`.
- Base: `dp[n][0] = dp[n][1] = 0`.
- Fill backward from `i = n-1`.

### Code

```cpp
int f(vector<int>& arr, int fee) {
    int n = arr.size();
    vector<vector<int>> dp(n + 1, vector<int>(2, 0));

    for (int i = n - 1; i >= 0; i--) {
        dp[i][1] = max(-arr[i] + dp[i + 1][0], dp[i + 1][1]);
        dp[i][0] = max(arr[i] - fee + dp[i + 1][1], dp[i + 1][0]);
    }
    return dp[0][1];
}
```

### Complexity Analysis

**Time Complexity:** `O(n)` – Iterate through all days × 2 states.

**Space Complexity:** `O(n)` – DP table.

---

## Space Optimization

- Only `ahead[2]` (for `i+1`) and `curr[2]` (for `i`) are needed.
- Reduce DP to 2 arrays of size 2.

### Code

```cpp
int f(vector<int>& arr, int fee) {
    int n = arr.size();
    vector<int> ahead(2, 0), curr(2, 0);

    for (int i = n - 1; i >= 0; i--) {
        curr[1] = max(-arr[i] + ahead[0], ahead[1]);
        curr[0] = max(arr[i] - fee + ahead[1], ahead[0]);
        ahead = curr;
    }
    return ahead[1];
}
```

### Complexity Analysis

**Time Complexity:** `O(n)` – One pass through days.

**Space Complexity:** `O(1)` – Only 2 arrays of constant size.

---

THE END
