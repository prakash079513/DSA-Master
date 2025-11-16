# **1641. Count Sorted Vowel Strings**

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

You are given an integer `n`. Your task is to count how many **lexicographically non-decreasing strings** of length `n` can be formed using only the vowels `a`, `e`, `i`, `o`, and `u`.

A string is lexicographically valid if each character is greater than or equal to the one before it.

Return the total number of such strings.

### Example 1

Input: `n = 2`

Valid strings include:

`aa, ae, ai, ao, au, ee, ei, eo, eu, ii, io, iu, oo, ou, uu`

Invalid examples:

`ea` (because `e > a` but appears before it),

`oa` (o appears before a)

Total valid strings for `n = 2` is 15.

### Example 2

Input: `n = 3`

Some valid strings:

`aaa, aae, aai, aao, aau, aee, aei, aio, ioo, ooo, oou, uuu`, etc.

Invalid examples:

`eaa` (e cannot come before a),

`ioa` (i > o > a is decreasing)

Total valid strings for `n = 3` is 35.

## Recursion

### Intuition

We construct the string character by character. At each position we choose one of the vowels. Because the final string must be lexicographically non-decreasing, if the previous character had index `last`, the current character can only be chosen from indices `last` to `4`.

Define a recursive function `rec(pos, last)` that returns the number of valid strings starting at position `pos` when the previous vowel index was `last`.

If `pos == n`, a complete valid string is formed, so return `1`.

Otherwise, try every vowel index `j` from `last` to `4` and sum the results.

### Approach

Use a recursive helper `rec(pos, last, n)`.

If `pos == n`, return `1`.

Otherwise, loop `j` from `last` to `4` and compute `rec(pos+1, j, n)`.

Initial call is `rec(0, 0, n)`.

### Code

```cpp
int rec(int pos, int last, int n) {
    if (pos == n) return 1;
    int ways = 0;
    for (int j = last; j < 5; j++) {
        ways += rec(pos + 1, j, n);
    }
    return ways;
}

int countVowelStrings(int n) {
    return rec(0, 0, n);
}
```

### Complexity Analysis

Time Complexity: `O(5^n)`

Space Complexity: `O(n)`

## Memoization

### Intuition

The recursion recalculates the same states repeatedly. The state is determined by `(pos, last)`.

We can memoize results in a DP table `dp[pos][last]`. If a state is already computed, we immediately return it instead of recomputing.

### Approach

Create a 2D array `dp[n+1][5]` initialized with `-1`.

Modify the recursive function so that before computing a state, it checks if `dp[pos][last]` is already computed.

If so, return it. Otherwise compute the value once, store it, and return it.

### Code

```cpp
int dp[205][5];

int rec(int pos, int last, int n) {
    if (pos == n) return 1;
    if (dp[pos][last] != -1) return dp[pos][last];

    int ways = 0;
    for (int j = last; j < 5; j++) {
        ways += rec(pos + 1, j, n);
    }
    return dp[pos][last] = ways;
}

int countVowelStrings(int n) {
    memset(dp, -1, sizeof(dp));
    return rec(0, 0, n);
}
```

### Complexity Analysis

Time Complexity: `O(5n)`

Space Complexity: `O(5n)` plus recursion stack `O(n)`

## Tabulation

### Intuition

Convert the memoized recursion into a bottom-up DP.

Define `dp[i][j]` as the number of valid strings of length `i` ending with vowel index `j`.

For length 1, all values are `1`.

For length `i >= 2`,

`dp[i][j] = dp[i-1][0] + dp[i-1][1] + ... + dp[i-1][j]`.

Answer is the sum of `dp[n][0]` to `dp[n][4]`.

### Approach

Initialize table with `dp[1][j] = 1`.

Fill from `i = 2` to `n` using cumulative sums of previous row.

Return the sum of the last row.

### Code

```cpp
int countVowelStrings(int n) {
    vector<vector<int>> dp(n + 1, vector<int>(5, 0));

    for (int j = 0; j < 5; j++) dp[1][j] = 1;

    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < 5; j++) {
            int sum = 0;
            for (int k = 0; k <= j; k++) {
                sum += dp[i - 1][k];
            }
            dp[i][j] = sum;
        }
    }

    int ans = 0;
    for (int j = 0; j < 5; j++) ans += dp[n][j];
    return ans;
}
```

### Complexity Analysis

Time Complexity: `O(5n)`

Space Complexity: `O(5n)`

## Space Optimization

### Intuition

To compute row `i`, we only need row `i-1`.

So instead of storing the entire DP table, we can use two arrays to store the previous row and current row.

Each `curr[j]` is computed as the prefix sum of `prev`.

### Approach

Maintain arrays `prev[5]` and `curr[5]`.

Initialize `prev` with all ones.

For each length from 2 to `n`, compute `curr` using prefix sums, then assign `curr` to `prev`.

Final answer is the sum of `prev`.

### Code

```cpp
int countVowelStrings(int n) {
    vector<int> prev(5, 1), curr(5, 0);

    for (int i = 2; i <= n; i++) {
        curr[0] = prev[0];
        for (int j = 1; j < 5; j++) {
            curr[j] = curr[j - 1] + prev[j];
        }
        prev = curr;
    }

    int ans = 0;
    for (int j = 0; j < 5; j++) ans += prev[j];
    return ans;
}
```

### Complexity Analysis

Time Complexity: `O(5n)`

Space Complexity: `O(5)`

---

THE END
