# Range Sum Query 2D – Immutable

Author: [Prakash JC](https://prakash079513.github.io)

## Problem Statement

You are given a 2D matrix `matrix` of integers.

Implement the class `NumMatrix` that supports the following operation:

- `NumMatrix(vector<vector<int>>& matrix)` – Initializes the object with the integer matrix.
- `int sumRegion(int row1, int col1, int row2, int col2)` – Returns the sum of elements inside the rectangle defined by its upper-left corner `(row1, col1)` and lower-right corner `(row2, col2)` (inclusive).

---

### Approach

**2D Prefix Sum Technique**

- Construct a 2D prefix sum matrix `prefix` such that:

Assume grid is

`1 2 3`

`4 5 6`

`7 8 9`

Point is to find the prefix sum so far of some random row and col say row 2 and col 1 (0 based indexing): value = 8

The answer will be: 8 + top rectangle sum(1 2 4 5) + left rectangle sum(1 4 7) - overlapped rect sum(1 4).

**Note:**

For row 0, we cant get the top sum, since it is the edge. So, to handle this we will add extra empty row above it and hence column beside it. So now the storage matrix prefix size will be `n+1*m+1` size and it will look like:

`0 0 0 0`

`0 x _ _`

`0 _ _ _`

`0 _ _ _`

### Do **1 based indexing** on the storage matrix prefix:

Formula to build prefix matrix:

```
prefix[r][c] = matrix[r-1][c-1]
             + prefix[r-1][c]
             + prefix[r][c-1]
             - prefix[r-1][c-1]
```

Explanation:

| r\c | 0   | 1   | 2   |
| --- | --- | --- | --- |
| 0   | 1   | 2   | 3   |
| 1   | 4   | 5   | 6   |
| 2   | 7   | 8   | 9   |

We’re focusing on the cell `(r=2, c=1)` → value = **8**.

In **1-indexed prefix notation**, this corresponds to **`prefix[3][2]`** (since prefix has one extra row and column).

### Formula

`prefix[i][j] = matrix[i-1][j-1] + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1]`

Now substitute:

- `i = 3`
- `j = 2`

So:

```
prefix[3][2] = matrix[2][1]
             + prefix[2][2]
             + prefix[3][1]
             - prefix[2][1]
```

### Step-by-step with actual numbers

Let’s fill in what each of those means:

| Term           | From which part                                         | Value | Explanation                                           |
| -------------- | ------------------------------------------------------- | ----- | ----------------------------------------------------- |
| `matrix[2][1]` | current cell                                            | `8`   | the element itself                                    |
| `prefix[2][2]` | top rectangle sum (above current row) (1, 2, 4, 5)      | `12`  | sum of elements in all rows above row=2, columns 0..1 |
| `prefix[3][1]` | left rectangle sum (same row, previous cols) ( 1, 4, 7) | `12`  | sum of elements in row 0..2, col 0                    |
| `prefix[2][1]` | overlap counted twice (top-left block) ( 1, 4)          | `5`   | sum of area covered by both above & left              |

So `prefix[3][2] = 27`.

---

### Visual Breakdown

Think of the area `(0,0)` → `(2,1)` (i.e., up to row=2, col=1):

```
1  2
4  5
7  8
```

Sum = `1 + 2 + 4 + 5 + 7 + 8 = 27`

And that’s exactly what we got from the formula.

---

To compute the sum of a region `(row1, col1)` to `(row2, col2)`:

```
sumRegion = prefix[row2 + 1][col2 + 1]
          - prefix[row1][col2 + 1]
          - prefix[row2 + 1][col1]
          + prefix[row1][col1]
```

---

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class NumMatrix {
    vector<vector<int>> prefix;
public:
    NumMatrix(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        prefix.assign(n + 1, vector<int>(m + 1, 0));

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                prefix[i][j] = matrix[i - 1][j - 1]
                             + prefix[i - 1][j]
                             + prefix[i][j - 1]
                             - prefix[i - 1][j - 1];
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return prefix[row2 + 1][col2 + 1]
             - prefix[row1][col2 + 1]
             - prefix[row2 + 1][col1]
             + prefix[row1][col1];
    }
};

int main() {
    vector<vector<int>> matrix = {
        {3, 0, 1, 4, 2},
        {5, 6, 3, 2, 1},
        {1, 2, 0, 1, 5},
        {4, 1, 0, 1, 7},
        {1, 0, 3, 0, 5}
    };
    NumMatrix s1(matrix);
    cout << s1.sumRegion(2, 1, 4, 3) << endl; // Output: 8
    cout << s1.sumRegion(1, 1, 2, 2) << endl; // Output: 11
    cout << s1.sumRegion(1, 2, 2, 4) << endl; // Output: 12
    return 0;
}
```

---

### Complexity Analysis

**Time Complexity:**

- Preprocessing: `O(n * m)` – Build prefix sum matrix.
- Each Query: `O(1)` – Uses constant-time arithmetic on prefix matrix.

**Space Complexity:** `O(n * m)` – For storing the prefix sum matrix.

---

THE END
