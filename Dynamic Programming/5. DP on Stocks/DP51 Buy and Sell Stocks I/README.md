# Best Time to Buy and Sell Stock I (Single Transaction)

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

You’re given an array `prices[]` where `prices[i]` is the price of a stock on day `i`. You must choose a **single day** to buy and a later day to sell, maximizing your profit. If no profit is possible, return `0`.

---

## Editorial

## Brute Force Approach

**Idea:**

Try **every possible buy and sell day** combination. For each pair `(i, j)` where `j > i`, compute `prices[j] - prices[i]` and track the maximum.

**Steps:**

1. Initialize `maxProfit = 0`.
2. Loop over all pairs of days:
   - Buy on `i`, sell on `j`.
   - If profit > `maxProfit`, update it.
3. Return `maxProfit`.

### **Code**

```cpp
int maxProfit(vector<int>& prices) {
    int n = prices.size();
    int maxProfit = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            maxProfit = max(maxProfit, prices[j] - prices[i]);
        }
    }
    return maxProfit;
}
```

### Complexity Analysis

**Time Complexity:** `O(n^2)` – Two nested loops over all pairs.

**Space Complexity:** `O(1)` – Only a few variables used.

---

## Optimal Approach

**Idea:**

The profit depends on finding the **lowest buying price so far** and the **maximum profit achievable at each step**.

We scan once:

- Keep track of the minimum price seen up to the current day.
- At each day, compute potential profit = `prices[i] - minPrice`.
- Update maxProfit if this is larger.

This way, every price is checked only once.

**Steps:**

1. Initialize `minPrice = INT_MAX`, `maxProfit = 0`.
2. Traverse prices:
   - Update `minPrice` = min(`minPrice`, `prices[i]`).
   - Update `maxProfit` = max(`maxProfit`, `prices[i] - minPrice`).
3. Return `maxProfit`.

### Code

```cpp
int maxProfit(vector<int>& prices) {
    int minPrice = INT_MAX;
    int maxProfit = 0;
    for (int price : prices) {
        minPrice = min(minPrice, price);
        maxProfit = max(maxProfit, price - minPrice);
    }
    return maxProfit;
}
```

### Complexity Analysis

**Time Complexity:** `O(n)` – Single pass through prices.

**Space Complexity:** `O(1)` – Constant extra space.

---

THE END
