# Partitions with Given Difference

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

Given an array with N positive integers and an integer D. Count the number of ways we can partition the given array into two subsets, S1 and S2 such that S1 - S2 = D and S1 is always greater than or equal to S2.

## Editorial

`S1 >= S2` (this is automatically satisfied when difference is `D >= 0`).

Let the total sum of the array = `sum`.

We know:

```
S1 + S2 = sum
S1 - S2 = D
```

Adding the two equations:

```
2 * S1 = sum + D
=> S1 = (sum + D) / 2
```

So, the problem **reduces to counting subsets with sum = (sum + D) / 2**.

Important conditions:

- `(sum + D)` must be even, else return 0.
- `(sum + D)/2` must be ≤ sum, else return 0.

Now it becomes a **Count Subsets with Given Sum** problem.

## Recursion

- **Parameters:** `idx` (current index), `target` (remaining sum).
- **Choices:** Either include the element or exclude it.
- **Base Case:**
  - If `idx == 0`:
    - If `target == 0` and `arr[0] == 0`: return 2 (either pick or not pick).
    - If `target == 0` or `target == arr[0]`: return 1.
    - Else return 0.

### Code

```cpp
int f(int idx, int target, vector<int>& arr) {
    if (idx == 0) {
        if (target == 0 && arr[0] == 0) return 2;
        if (target == 0 || target == arr[0]) return 1;
        return 0;
    }
    int notTake = f(idx - 1, target, arr);
    int take = 0;
    if (arr[idx] <= target)
        take = f(idx - 1, target - arr[idx], arr);
    return take + notTake;
}
```

### **Complexity Analysis**

**Time Complexity:** `O(2^n)` - Every element has two choices.

**Space Complexity:** `O(n)` - Recursion stack.

---

## Memoization

### Code

```cpp
int f(int idx, int target, vector<int>& arr, vector<vector<int>>& dp) {
    if (idx == 0) {
        if (target == 0 && arr[0] == 0) return 2;
        if (target == 0 || target == arr[0]) return 1;
        return 0;
    }
    if (dp[idx][target] != -1) return dp[idx][target];

    int notTake = f(idx - 1, target, arr, dp);
    int take = 0;
    if (arr[idx] <= target)
        take = f(idx - 1, target - arr[idx], arr, dp);

    return dp[idx][target] = take + notTake;
}
```

### **Complexity Analysis**

**Time Complexity:** `O(n * target)` - Each state computed once.

**Space Complexity:** `O(n * target)` - DP table + recursion stack.

---

## Tabulation

### Code

```cpp
int f(vector<int>& arr, int target) {
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(target + 1, 0));

    if (arr[0] == 0) dp[0][0] = 2;
    else dp[0][0] = 1;
    if (arr[0] != 0 && arr[0] <= target) dp[0][arr[0]] = 1;

    for (int i = 1; i < n; i++) {
        for (int t = 0; t <= target; t++) {
            int notTake = dp[i - 1][t];
            int take = 0;
            if (arr[i] <= t) take = dp[i - 1][t - arr[i]];
            dp[i][t] = take + notTake;
        }
    }
    return dp[n - 1][target];
}
```

### **Complexity Analysis**

**Time Complexity:** `O(n * target)` - Iterative filling.

**Space Complexity:** `O(n * target)` - DP table.

---

## Space Optimization

### Code

```cpp
int f(vector<int>& arr, int target) {
    int n = arr.size();
    vector<int> prev(target + 1, 0), curr(target + 1, 0);

    if (arr[0] == 0) prev[0] = 2;
    else prev[0] = 1;
    if (arr[0] != 0 && arr[0] <= target) prev[arr[0]] = 1;

    for (int i = 1; i < n; i++) {
        for (int t = 0; t <= target; t++) {
            int notTake = prev[t];
            int take = 0;
            if (arr[i] <= t) take = prev[t - arr[i]];
            curr[t] = take + notTake;
        }
        prev = curr;
    }
    return prev[target];
}
```

### **Complexity Analysis**

**Time Complexity:** `O(n * target)` - Still same loops.

**Space Complexity:** `O(target)` - Only 1D array needed.

---

THE END
