# Buy and Sell Stocks 2

Author: [Prakash JC](https://prakash079513.github.io/)

## Problem Statement

We are given an array `Arr[]` of length `n`. Each element represents the price of a stock on that day.

We are allowed to **buy and sell the stock multiple times**, under the following rules:

1. We must **buy before we sell**.
2. After buying, we cannot buy again until we sell.
3. After selling, we can buy again.

We need to calculate the **maximum profit** achievable.

---

## Editorial

At each day, we have **two states**:

- **Can Buy**: We are free to either buy the stock or skip.
- **Can’t Buy (Must Sell/Skip)**: We already own a stock, so we can either sell it or skip.

This leads naturally to a **state machine DP**.

---

## Recursion

- Define a function `f(i, canBuy)` where:
  - `i` = current day (0 to n-1).
  - `canBuy` = 1 if we are allowed to buy, 0 if we must sell before buying again.
- Choices:
  - If `canBuy == 1`:
    - **Buy** → profit = `Arr[i] + f(i+1, 0)`
    - **Skip** → profit = `f(i+1, 1)`
  - If `canBuy == 0`:
    - **Sell** → profit = `Arr[i] + f(i+1, 1)`
    - **Skip** → profit = `f(i+1, 0)`
- Take maximum of choices.
- Base case: If `i == n`, return `0` (no days left).

### Code

```cpp
int f(int i, int canBuy, vector<int>& arr, int n) {
    if (i == n) return 0;

    if (canBuy) {
        int buy = -arr[i] + f(i + 1, 0, arr, n);
        int skip = f(i + 1, 1, arr, n);
        return max(buy, skip);
    } else {
        int sell = arr[i] + f(i + 1, 1, arr, n);
        int skip = f(i + 1, 0, arr, n);
        return max(sell, skip);
    }
}
```

### Complexity Analysis

**Time Complexity:** `O(2^n)` – Each day leads to two choices.

**Space Complexity:** `O(n)` – Recursion stack.

---

## Memoization

- Use `dp[i][canBuy]` to store the result for state `(i, canBuy)`.
- If already computed, return from `dp`.

### Code

```cpp
int f(int i, int canBuy, vector<int>& arr, int n, vector<vector<int>>& dp) {
    if (i == n) return 0;

    if (dp[i][canBuy] != -1) return dp[i][canBuy];

    if (canBuy) {
        int buy = -arr[i] + f(i + 1, 0, arr, n, dp);
        int skip = f(i + 1, 1, arr, n, dp);
        return dp[i][canBuy] = max(buy, skip);
    } else {
        int sell = arr[i] + f(i + 1, 1, arr, n, dp);
        int skip = f(i + 1, 0, arr, n, dp);
        return dp[i][canBuy] = max(sell, skip);
    }
}
```

### Complexity Analysis

**Time Complexity:** `O(n * 2)` – Each `(i, canBuy)` solved once.

**Space Complexity:** `O(n * 2)` (DP table) + `O(n)` recursion stack.

---

## Tabulation

- Bottom-up filling of `dp[i][canBuy]`.
- Dimensions: `n+1` × `2`.
- Base case: `dp[n][0] = dp[n][1] = 0` (no profit possible after last day).

### Code

```cpp
int maxProfit(vector<int>& arr) {
    int n = arr.size();
    vector<vector<int>> dp(n + 1, vector<int>(2, 0));

    for (int i = n - 1; i >= 0; i--) {
        dp[i][1] = max(-arr[i] + dp[i + 1][0], dp[i + 1][1]);
        dp[i][0] = max(arr[i] + dp[i + 1][1], dp[i + 1][0]);
    }

    return dp[0][1]; // start with canBuy = 1
}
```

### Complexity Analysis

**Time Complexity:** `O(n * 2)` – Every state computed once.

**Space Complexity:** `O(n * 2)` – DP table storage.

---

## Space Optimization

- At day `i`, we only need results from day `i+1`.
- Use two arrays: `ahead[2]` and `curr[2]`.

### Code

```cpp
int maxProfit(vector<int>& arr) {
    int n = arr.size();
    vector<int> ahead(2, 0), curr(2, 0);

    for (int i = n - 1; i >= 0; i--) {
        curr[1] = max(-arr[i] + ahead[0], ahead[1]);
        curr[0] = max(arr[i] + ahead[1], ahead[0]);
        ahead = curr;
    }

    return ahead[1]; // canBuy = 1
}
```

### Complexity Analysis

**Time Complexity:** `O(n)` – Each day processed once.

**Space Complexity:** `O(2)` = `O(1)` – Only two 1D arrays used.

---

THE END
