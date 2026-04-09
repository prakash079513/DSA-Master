## **1295. Find Numbers with Even Number of Digits**

Author: Prakash JC

## Problem Statement

Given an array `nums` of integers, return how many of them contain an **even number of digits**.

---

### Key Takeaway

- Divide by 10 or use range-based shortcuts.

---

## Brute Force Approach

### Approach

- Traverse each element in the array
- Convert each number to string
- Check length of string
- If length is even, increment count
- Return count

**Time Complexity: `O(n * d)`**

**Space Complexity:** `O(d)`

---

## Approach 2 – Digit Counting (Best General Solution)

### Key Observation

- Number of digits can be found by repeatedly dividing by 10
- Works for **all ranges**, no assumptions needed

### Approach

- Initialize count = 0
- Traverse array
- For each number:
  - Count digits using `while(x > 0)`
  - If digit count is even → increment answer
- Return count

---

## Code

```cpp
int findNumbers(vector<int>& nums) {
    int count = 0;

    for (int i = 0; i < nums.size(); i++) {
        int x = nums[i];
        int digits = 0;

        while (x > 0) {
            digits++;
            x /= 10;
        }

        if (digits % 2 == 0)
            count++;
    }

    return count;
}
```

---

## Approach 3 – Range Check (Fastest but Limited)

### Key Observation

- Instead of counting digits, directly check ranges:
  - 2-digit → 10–99
  - 4-digit → 1000–9999
  - 6-digit → 100000
- This works because constraints are small and fixed

### Approach

- Traverse array
- Check if number lies in even-digit ranges
- Increment count accordingly

## Code

```cpp
int findNumbers(vector<int>& nums) {
    int evenDigitCount = 0;

    for (int num : nums) {
        if ((num >= 10 && num <= 99) ||
            (num >= 1000 && num <= 9999) ||
            num == 100000)
            evenDigitCount++;
    }

    return evenDigitCount;
}
```

---

**Time Complexity:** `O(n * d)` – digit counting per number

**Space Complexity:** `O(1)` – constant space

---

THE END
