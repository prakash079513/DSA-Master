# Sum Except First and Last

Author: [Prakash JC](https://github.com/prakash079513)

## Problem Statement

You are given an array `arr` of numbers. Return the sum of all the elements **except** the **first** and **last** elements.

### Examples:

- **Input**: `arr[] = [5, 24, 39, 60, 15, 28, 27, 40, 50, 90]`
  **Output**: `283`
  **Explanation**: The sum of all the elements except the first and last element is 283.
- **Input**: `arr[] = [5, 10, 1, 11]`
  **Output**: `11`
  **Explanation**: The sum of all the elements except the first and last element is 11.
- **Input**: `arr[] = [5, 10]`
  **Output**: `0`
  **Explanation**: The sum of all the elements except the first and last element is 0.

### Constraints:

- `2 <= arr.size() <= 10⁵`
- `2 <= arr[i] <= 10⁵`

---

# Editorial

## Brute Force Approach

### Approach:

- Traverse the array from index `1` to `n-2`.
- Keep adding each element to a `sum` variable.
- Return the `sum`.

### Code:

**C++:**

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int sumExceptFirstAndLast(vector<int>& arr) {
        int n = arr.size();
        if(n <= 2) return 0;

        int sum = 0;
        for(int i = 1; i < n - 1; i++) {
            sum += arr[i];
        }
        return sum;
    }
};

int main() {
    vector<int> arr = {5, 24, 39, 60, 15, 28, 27, 40, 50, 90};
    Solution s1;
    cout << s1.sumExceptFirstAndLast(arr);
    return 0;
}
```

**Python:**

```cpp
class Solution:
    def sumExceptFirstAndLast(self, arr):
        n = len(arr)
        if n <= 2:
            return 0
        total = 0
        for i in range(1, n - 1):
            total += arr[i]
        return total

if __name__ == "__main__":
    arr = [5, 24, 39, 60, 15, 28, 27, 40, 50, 90]
    s1 = Solution()
    print(s1.sumExceptFirstAndLast(arr))
```

### Complexity Analysis:

- **Time Complexity**: `O(n)`
- **Space Complexity**: `O(1)`

---

## Optimal Approach

### Approach:

- Use built-in functions or slicing.
- Take sum of the array from `index 1 to index n-2`.

### Code:

**C++:**

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int sumExceptFirstAndLast(vector<int>& arr) {
        if(arr.size() <= 2) return 0;
        return accumulate(arr.begin() + 1, arr.end() - 1, 0);
    }
};

int main() {
    vector<int> arr = {5, 24, 39, 60, 15, 28, 27, 40, 50, 90};
    Solution s1;
    cout << s1.sumExceptFirstAndLast(arr);
    return 0;
}
```

**Python:**

```cpp
class Solution:
    def sumExceptFirstAndLast(self, arr):
        return sum(arr[1:-1]) if len(arr) > 2 else 0

if __name__ == "__main__":
    arr = [5, 24, 39, 60, 15, 28, 27, 40, 50, 90]
    s1 = Solution()
    print(s1.sumExceptFirstAndLast(arr))
```

### Complexity Analysis:

- **Time Complexity**: `O(n)`
- **Space Complexity**: `O(1)` for C++, `O(n)` in Python slicing (due to temporary copy of sublist)

---

THE END
