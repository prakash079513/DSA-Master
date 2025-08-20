# Inverted Star Pyramid

Author: [Prakash JC](https://github.com/prakash079513)

### Problem Statement

Print the following inverted pyramid pattern of height `n` . For `n = 6` :

```
***********
 *********
  *******
   *****
    ***
     *
```

### Approach

1. Iterate through rows from `0` to `n-1`.
2. For each row:
   - Print `i` spaces.
   - Print `(2 * (n - i) - 1)` stars.
3. Move to the next line after finishing each row.

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void printInvertedPattern(int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) cout << " ";
            for (int j = 0; j < 2 * (n - i) - 1; j++) cout << "*";
            cout << "\n";
        }
    }
};

int main() {
    int n = 6; // height of inverted pyramid
    Solution s1;
    s1.printInvertedPattern(n);
    return 0;
}
```

### Complexity Analysis

**Time Complexity:** `O(n²)` - We print roughly n² characters in total.

**Space Complexity:** `O(1)` - Only loop counters are used.

---

THE END
