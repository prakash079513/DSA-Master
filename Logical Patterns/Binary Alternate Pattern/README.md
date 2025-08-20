# Binary Alternate Pattern

Author: [Prakash JC](https://github.com/prakash079513)

### Problem Statement

Print the following binary alternate pattern for a given `n` . For `n = 6` :

```
1
01
101
0101
10101
010101
```

### Approach

1. Iterate over rows `i` from `1` to `n`.
2. Decide the starting digit for the row:
   - If `i` is odd → start with `1`.
   - If `i` is even → start with `0`.
3. Alternate between `1` and `0` while printing characters across the row.
4. After finishing one row, move to the next line.

This ensures the alternating binary sequence while respecting row parity.

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void printBinaryPattern(int n) {
        for (int i = 1; i <= n; i++) {
            int start = (i % 2 == 1) ? 1 : 0; // odd row -> start 1, even row -> start 0
            for (int j = 0; j < i; j++) {
                cout << (start + j) % 2;
            }
            cout << "\n";
        }
    }
};

int main() {
    int n = 6; // number of rows
    Solution s1;
    s1.printBinaryPattern(n);
    return 0;
}
```

## Complexity Analysis

**Time Complexity:** `O(n²)` - Because we print 1 + 2 + … + n ≈ n²/2 characters.

**Space Complexity:** `O(1)` - Only loop counters and a temporary variable are used.

---

THE END
