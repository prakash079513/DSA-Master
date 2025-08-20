# Diamond Pyramid

Author: [Prakash JC](https://github.com/prakash079513)

### Problem Statement

Given an integer n (height of the top pyramid), print:

- An upright pyramid from 1 to (2n−1) stars,
- The widest line again once (duplicate peak),
- Then an inverted pyramid back down to 1 star.

For n = 6, the output is:

```
     *
    ***
   *****
  *******
 *********
***********
***********
 *********
  *******
   *****
    ***
     *
```

### Approach

1. Top pyramid: for each row i from 0 to n−1
   - Print `(n−i−1)` spaces
   - Print `(2i+1)` stars
2. Duplicate peak: print exactly `(2n−1)` stars once.
3. Bottom pyramid: for i from n−2 down to 0
   - Print `(n−i−1)` spaces
   - Print `(2i+1)` stars

This directly constructs the required shape with a single pass of simple loops.

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void printDoublePeakDiamond(int n) {
        if (n <= 0) return;

        // Top pyramid
        for (int i = 0; i < n; i++) {
            for (int s = 0; s < n - i - 1; s++) cout << " ";
            for (int k = 0; k < 2 * i + 1; k++) cout << "*";
            cout << "\n";
        }

        // Duplicate peak line
        for (int k = 0; k < 2 * n - 1; k++) cout << "*";
        cout << "\n";

        // Bottom pyramid
        for (int i = n - 2; i >= 0; i--) {
            for (int s = 0; s < n - i - 1; s++) cout << " ";
            for (int k = 0; k < 2 * i + 1; k++) cout << "*";
            cout << "\n";
        }
    }
};

int main() {
    int n = 6; // height of the top pyramid
    Solution s1;
    s1.printDoublePeakDiamond(n);
    return 0;
}
```

### Complexity Analysis

**Time Complexity:** `O(n²)` - Total characters printed across all lines sum to a quadratic order in n.

**Space Complexity:** `O(1)` - Only loop counters are used; no extra data structures.

---

THE END
