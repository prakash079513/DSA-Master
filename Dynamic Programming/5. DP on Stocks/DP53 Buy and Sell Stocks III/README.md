# Best Time to Buy and Sell Stock III

Author: [Prakash JC](https://prakash079513.github.io/)

---

## Problem Statement

We are given an array `Arr[]` of size `n` where each element represents the price of a stock on day `i`.

We are allowed to complete at most **2 transactions**.

Each transaction consists of **buying one stock and selling it once later**.

We need to calculate the **maximum profit** achievable.

---

## Editorial

Here, unlike the unlimited transactions case, we are restricted to **at most 2 transactions**.

This introduces an extra dimension: **how many transactions are left**.

So the DP state becomes:

- `i` → current day.
- `canBuy` → whether we can buy (1 = yes, 0 = must sell first).
- `cap` → how many transactions are remaining (max 2 initially).

---

## Recursion

- Define `f(i, canBuy, cap)`:
  - If `cap == 0` → no transactions left, return 0.
  - If `i == n` → no days left, return 0.
- Choices:
  - If `canBuy == 1`:
    - Buy → `Arr[i] + f(i+1, 0, cap)`
    - Skip → `f(i+1, 1, cap)`
  - If `canBuy == 0`:
    - Sell → `Arr[i] + f(i+1, 1, cap-1)`
    - Skip → `f(i+1, 0, cap)`

Take the maximum.

---

### Code

```cpp
int f(int i, int canBuy, int cap, vector<int>& arr, int n) {
    if (cap == 0 || i == n) return 0;

    if (canBuy) {
        int buy = -arr[i] + f(i + 1, 0, cap, arr, n);
        int skip = f(i + 1, 1, cap, arr, n);
        return max(buy, skip);
    } else {
        int sell = arr[i] + f(i + 1, 1, cap - 1, arr, n);
        int skip = f(i + 1, 0, cap, arr, n);
        return max(sell, skip);
    }
}
```

### Complexity Analysis

**Time Complexity:** `O(2^n)` – Each day splits into two choices.

**Space Complexity:** `O(n)` – Recursion depth.

---

## Memoization

- Store results in `dp[i][canBuy][cap]`.
- Before computing, check if already available.

### Code

```cpp
int f(int i, int canBuy, int cap, vector<int>& arr, int n, vector<vector<vector<int>>>& dp) {
    if (cap == 0 || i == n) return 0;
    if (dp[i][canBuy][cap] != -1) return dp[i][canBuy][cap];

    if (canBuy) {
        int buy = -arr[i] + f(i + 1, 0, cap, arr, n, dp);
        int skip = f(i + 1, 1, cap, arr, n, dp);
        return dp[i][canBuy][cap] = max(buy, skip);
    } else {
        int sell = arr[i] + f(i + 1, 1, cap - 1, arr, n, dp);
        int skip = f(i + 1, 0, cap, arr, n, dp);
        return dp[i][canBuy][cap] = max(sell, skip);
    }
}
```

### Complexity Analysis

**Time Complexity:** `O(n * 2 * 3)` – Each `(i, canBuy, cap)` computed once.

**Space Complexity:** `O(n * 2 * 3)` + `O(n)` recursion stack.

---

## Tabulation

- Build `dp[n+1][2][3]`.
- Base: `dp[n][*][*] = 0`.
- Fill bottom-up.

### Code

```cpp
int maxProfit(vector<int>& arr) {
    int n = arr.size();
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(3, 0)));

    for (int i = n - 1; i >= 0; i--) {
        for (int canBuy = 0; canBuy <= 1; canBuy++) {
            for (int cap = 1; cap <= 2; cap++) {
                if (canBuy) {
                    dp[i][canBuy][cap] = max(-arr[i] + dp[i + 1][0][cap], dp[i + 1][1][cap]);
                } else {
                    dp[i][canBuy][cap] = max(arr[i] + dp[i + 1][1][cap - 1], dp[i + 1][0][cap]);
                }
            }
        }
    }

    return dp[0][1][2];
}
```

### Complexity Analysis

**Time Complexity:** `O(n * 2 * 3)` – Each state computed once.

**Space Complexity:** `O(n * 2 * 3)` – DP table storage.

---

## Space Optimization

- At `i`, only need `i+1`.
- Use two 2D arrays `ahead[2][3]` and `curr[2][3]`.

### Code

```cpp
int maxProfit(vector<int>& arr) {
    int n = arr.size();
    vector<vector<int>> ahead(2, vector<int>(3, 0)), curr(2, vector<int>(3, 0));

    for (int i = n - 1; i >= 0; i--) {
        for (int canBuy = 0; canBuy <= 1; canBuy++) {
            for (int cap = 1; cap <= 2; cap++) {
                if (canBuy) {
                    curr[canBuy][cap] = max(-arr[i] + ahead[0][cap], ahead[1][cap]);
                } else {
                    curr[canBuy][cap] = max(arr[i] + ahead[1][cap - 1], ahead[0][cap]);
                }
            }
        }
        ahead = curr;
    }

    return ahead[1][2];
}
```

### Complexity Analysis

**Time Complexity:** `O(n * 2 * 3)` – Each state computed once.

**Space Complexity:** `O(2 * 3)` = `O(1)` – Only two 2D arrays used.

---

THE END
