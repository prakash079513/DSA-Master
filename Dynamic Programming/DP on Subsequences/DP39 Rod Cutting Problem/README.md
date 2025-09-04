# Rod Cutting Problem

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

Given a rod of length `N` and an array `price[]` where `price[i]` represents the value of a rod piece of length `i+1`, determine the **maximum value** obtainable by cutting the rod into pieces. You can cut the rod in any way, and you may use each piece length **any number of times**.

---

## Understanding the Problem

- We are given a rod of length `N`.
- We can either cut it into multiple smaller pieces or use it as a whole.
- For each possible piece length `(1 to N)`, we know the selling price.
- Our goal is to **maximize total selling price** by choosing how to cut.
- This is essentially the same as:
  - We have `N` items (piece lengths).
  - Each item has a **weight = piece length** and a **value = price of that length**.
  - The rod length `N` is the **knapsack capacity**.
- Hence, **Rod Cutting is a direct variation of the Unbounded Knapsack Problem**.

---

## Recursion

- At each index `i` (representing piece length `i+1`), we have two choices:
  1. **Not take** this piece → move to smaller index.
  2. **Take** this piece → add `price[i]` and reduce rod length by `(i+1)`, but stay at the same index since unlimited usage is allowed.
- Base case:
  - If `i == 0`, the only possible cut is length `1`. We can take as many pieces of length `1` as possible → `N * price[0]`.

### Code

```cpp
int f(int i, int N, vector<int>& price) {
    if (i == 0) {
        return N * price[0];
    }

    int notTake = f(i - 1, N, price);
    int take = INT_MIN;
    int rodLength = i + 1;
    if (rodLength <= N) {
        take = price[i] + f(i, N - rodLength, price);
    }

    return max(take, notTake);
}
```

### Complexity Analysis

**Time Complexity:** `O(2^N)` – At each step, explore take/not-take recursively.

**Space Complexity:** `O(N)` – Recursion stack depth.

---

## Memoization

- Use a DP table `dp[i][N]` to store maximum obtainable value with rod length `N` using pieces up to index `i`.
- If already computed, return stored result.

### Code

```cpp
int f(int i, int N, vector<int>& price, vector<vector<int>>& dp) {
    if (i == 0) {
        return N * price[0];
    }

    if (dp[i][N] != -1) return dp[i][N];

    int notTake = f(i - 1, N, price, dp);
    int take = INT_MIN;
    int rodLength = i + 1;
    if (rodLength <= N) {
        take = price[i] + f(i, N - rodLength, price, dp);
    }

    return dp[i][N] = max(take, notTake);
}
```

### Complexity Analysis

**Time Complexity:** `O(N * N)` – Each state `(i, N)` computed once.

**Space Complexity:** `O(N * N)` DP table + `O(N)` recursion stack.

---

## Tabulation

- Build a 2D DP table iteratively.
- Base case:
  - For `i = 0`, `dp[0][len] = len * price[0]`.
- Transition:
  - `dp[i][len] = max(dp[i-1][len], price[i] + dp[i][len - (i+1)])`.

### Code

```cpp
int rodCutting(int N, vector<int>& price) {
    vector<vector<int>> dp(N, vector<int>(N + 1, 0));

    for (int len = 0; len <= N; len++) {
        dp[0][len] = len * price[0];
    }

    for (int i = 1; i < N; i++) {
        for (int len = 0; len <= N; len++) {
            int notTake = dp[i - 1][len];
            int take = INT_MIN;
            int rodLength = i + 1;
            if (rodLength <= len) {
                take = price[i] + dp[i][len - rodLength];
            }
            dp[i][len] = max(take, notTake);
        }
    }

    return dp[N - 1][N];
}
```

### Complexity Analysis

**Time Complexity:** `O(N * N)` – Double loop over items and lengths.

**Space Complexity:** `O(N * N)` – Full DP table.

---

## Space Optimization (Two Arrays)

- Only need previous row and current row.

### Code

```cpp
int rodCutting(int N, vector<int>& price) {
    vector<int> prev(N + 1, 0), curr(N + 1, 0);

    for (int len = 0; len <= N; len++) {
        prev[len] = len * price[0];
    }

    for (int i = 1; i < N; i++) {
        for (int len = 0; len <= N; len++) {
            int notTake = prev[len];
            int take = INT_MIN;
            int rodLength = i + 1;
            if (rodLength <= len) {
                take = price[i] + curr[len - rodLength];
            }
            curr[len] = max(take, notTake);
        }
        prev = curr;
    }

    return prev[N];
}
```

### Complexity Analysis

**Time Complexity:** `O(N * N)` – Iterating over all states.

**Space Complexity:** `O(2 * N)` → simplified to `O(N)`.

---

## Space Optimization (Single Array)

- Since `take` uses the **current row**, we can optimize further to a single array.
- Iterate lengths from `0 → N`.

### Code

```cpp
int rodCutting(int N, vector<int>& price) {
    vector<int> dp(N + 1, 0);

    for (int len = 0; len <= N; len++) {
        dp[len] = len * price[0];
    }

    for (int i = 1; i < N; i++) {
        for (int len = 0; len <= N; len++) {
            int notTake = dp[len];
            int take = INT_MIN;
            int rodLength = i + 1;
            if (rodLength <= len) {
                take = price[i] + dp[len - rodLength];
            }
            dp[len] = max(take, notTake);
        }
    }

    return dp[N];
}
```

### Complexity Analysis

**Time Complexity:** `O(N * N)` – Same transitions.

**Space Complexity:** `O(N)` – Single array maintained.

---

THE END
