# Pyramid Pattern

Author: [Prakash JC](https://github.com/prakash079513)

### Problem Statement

Print the following pyramid pattern of height `n`:

```markdown
     *
    ***

---

---

---

---
```

### Approach

1. Iterate through rows from `0` to `n-1`.
2. For each row:
   - Print `(n - i - 1)` spaces.
   - Print `(2 * i + 1)` stars.
3. Move to the next line after finishing each row.

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void printPattern(int n) {
        for (int i = 0; i < n; i++) {

            for (int j = 0; j < n - i - 1; j++) cout << " ";

            for (int j = 0; j < 2 * i + 1; j++) cout << "*";
            cout << "\n";
        }
    }
};

int main() {
    int n = 6;
    Solution s1;
    s1.printPattern(n);
    return 0;
}
```

### Complexity Analysis

Time Complexity: `O(n²)` - Because the total number of printed characters is proportional to n².

Space Complexity: `O(1)` - Only loop counters are used.

---

THE END
