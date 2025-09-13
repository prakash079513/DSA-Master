# Best Time to Buy and Sell Stock with Cooldown

Author: [Prakash JC](https://prakash079513.github.io/)

## Problem Statement

We are given an array `Arr[]` of length `n`, where `Arr[i]` represents the stock price on day `i`.

We can complete as many transactions as we like, but:

- After selling a stock, **you cannot buy on the very next day** (must cooldown for 1 day).
- Only one stock can be held at a time.

We must return the **maximum profit** achievable.

---

## Editorial

### Recursion

- Define a function `f(i, buy)`:
  - `i`: current day.
  - `buy`: 1 if we are allowed to buy, 0 if we need to sell.
- Choices:
  - If `buy == 1`:
    - Buy → `Arr[i] + f(i+1, 0)`
    - Skip → `f(i+1, 1)`
  - If `buy == 0`:
    - Sell → `Arr[i] + f(i+2, 1)` (skip one day for cooldown)
    - Skip → `f(i+1, 0)`
- Base case: if `i >= n`, return 0.

### Code

```cpp
int f(int i, int buy, vector<int>& arr, int n) {
    if (i >= n) return 0;

    if (buy) {
        int take = -arr[i] + f(i + 1, 0, arr, n);
        int notTake = f(i + 1, 1, arr, n);
        return max(take, notTake);
    } else {
        int sell = arr[i] + f(i + 2, 1, arr, n);
        int notSell = f(i + 1, 0, arr, n);
        return max(sell, notSell);
    }
}
```

### Complexity Analysis

**Time Complexity:** `O(2^n)` – Every day has two choices.

**Space Complexity:** `O(n)` – Recursion stack.

---

## Memoization

- Store results in `dp[i][buy]`.
- Return stored value if already calculated.

### Code

```cpp
int f(int i, int buy, vector<int>& arr, int n, vector<vector<int>>& dp) {
    if (i >= n) return 0;
    if (dp[i][buy] != -1) return dp[i][buy];

    if (buy) {
        int take = -arr[i] + f(i + 1, 0, arr, n, dp);
        int notTake = f(i + 1, 1, arr, n, dp);
        return dp[i][buy] = max(take, notTake);
    } else {
        int sell = arr[i] + f(i + 2, 1, arr, n, dp);
        int notSell = f(i + 1, 0, arr, n, dp);
        return dp[i][buy] = max(sell, notSell);
    }
}
```

### Complexity Analysis

**Time Complexity:** `O(n * 2)` → `O(n)`.

**Space Complexity:** `O(n * 2)` for dp + `O(n)` recursion stack.

---

## Tabulation

- Build DP array `dp[n+2][2]` (extra 2 to handle cooldown index safely).
- Start from last day → move backwards.

### Code

```cpp
int f(vector<int>& arr) {
    int n = arr.size();
    vector<vector<int>> dp(n + 2, vector<int>(2, 0));

    for (int i = n - 1; i >= 0; i--) {
        dp[i][1] = max(-arr[i] + dp[i + 1][0], dp[i + 1][1]);
        dp[i][0] = max(arr[i] + dp[i + 2][1], dp[i + 1][0]);
    }
    return dp[0][1];
}
```

### Complexity Analysis

**Time Complexity:** `O(n)` – Iterate days × 2 states.

**Space Complexity:** `O(n)` – DP table of size `[n+2][2]`.

---

## Space Optimization

- Only future states `ahead1` (i+1) and `ahead2` (i+2) are needed.
- Compress DP to **3 arrays**: `curr`, `ahead1`, `ahead2`.

### Code

```cpp
int f(vector<int>& arr) {
    int n = arr.size();
    vector<int> ahead1(2, 0), ahead2(2, 0), curr(2, 0);

    for (int i = n - 1; i >= 0; i--) {
        curr[1] = max(-arr[i] + ahead1[0], ahead1[1]);
        curr[0] = max(arr[i] + ahead2[1], ahead1[0]);
        ahead2 = ahead1;
        ahead1 = curr;
    }
    return ahead1[1];
}
```

### Complexity Analysis

**Time Complexity:** `O(n)` – Process each day.

**Space Complexity:** `O(1)` – Only 3 small arrays.

---

THE END
