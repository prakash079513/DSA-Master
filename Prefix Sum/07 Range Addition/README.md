# **Range Addition**

**LeetCode #370**

Author: [Prakash JC](https://prakash079513.github.io)

## **Problem Statement**

You are given an integer `length` representing the size of an initially zero-initialized array `nums` of size `length`.

You are also given `updates`, where each update is an array of the form

`[startIndex, endIndex, increment]`.

For each update, you must add `increment` to every element from `startIndex` to `endIndex` (inclusive).

Return the modified array after all updates.

## **Brute Force (For each update, update the array)**

### **Approach**

- Start with an array `nums` of size `length` initialized to `0`.
- For each update `[l, r, val]`, loop from `l` to `r` and add `val`.
- Slow because many updates may overlap, causing repeated work.
- Direct and simple but inefficient.

---

### **Code**

```cpp
vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
    vector<int> nums(length, 0);
    for (auto &u : updates) {
        int l = u[0], r = u[1], val = u[2];
        for (int i = l; i <= r; i++) nums[i] += val;
    }
    return nums;
}
```

---

### **Complexity Analysis**

**Time Complexity:** `O(n * m)` – For each update, apply increment across range.

**Space Complexity:** `O(n)` – Final array.

## **Prefix Add, Then Prefix Sum (Difference Array Method)**

**Expected Optimal Approach**

### **Approach**

- Instead of updating every element in `[l, r]`, update only:
  - `diff[l] += val`
  - `diff[r+1] -= val`
- After all updates, take prefix sum over `diff` to reconstruct the final array.
- This captures the effect of range additions in constant time per update.
- Only one final pass is needed to form the actual values.

### Dry Run

```cpp
n = 5, updates = [[1, 3, 2], [2, 4, 3], [0, 2, -2]]
```

We build a diff array of size `n + 1` :

`diff = [0 0 0 0 0 0]` (6 elements)

**Update 1: [1, 3, 2] :** diff = [0 2 0 0 -2 0]

Here if you take the prefix sum: the array will be: `[0 2 2 2 0]` which is what we need.

Hence do the difference thing for all the updates, then finally calculate the prefix sum.

Other updates:

**Update 1: [2, 4, 3] :** diff = [0 2 3 0 -2 -3]

**Update 1: [0, 2, -2] :** diff = [-2 2 3 2 -2 -3]

Now compute prefix sum to get final array:`arr[i] = diff[0] + diff[1] + ... + diff[i]`

Final answer: `[-2, 0, 3, 5, 3]`

---

### **Code**

```cpp
vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
    vector<int> diff(length+1, 0);

    for (auto &u : updates) {
        int l = u[0], r = u[1], val = u[2];
        diff[l] += val;
        if (r + 1 < length) diff[r+1] -= val;
    }

    vector<int> ans(length, 0);
    int curr = 0;
    for (int i = 0; i < length; i++) {
        curr += diff[i];
        ans[i] = curr;
    }

    return ans;
}
```

---

### **Complexity Analysis**

**Time Complexity:** `O(n + m)` – `m` updates processed in `O(1)` each, then one prefix pass.

**Space Complexity:** `O(n)` – Difference + result array.

## **Sweep Line Interval Logic (Alternate Interpretation)**

_(Same idea as difference array but conceptualized differently)_

### **Approach**

- Treat each update as:
  - Add `val` at `l`
  - Remove `val` after `r`
- Maintain an events array:
  - `events[l] += val`
  - `events[r+1] -= val`
- Accumulate these events using prefix sum.
- Identical output to the difference technique but expressed as a sweep-line.

---

### **Code**

```cpp
vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
    vector<int> events(length+1, 0);

    for (auto &u : updates) {
        events[u[0]] += u[2];
        if (u[1] + 1 < length) events[u[1] + 1] -= u[2];
    }

    vector<int> ans(length, 0);
    int active = 0;
    for (int i = 0; i < length; i++) {
        active += events[i];
        ans[i] = active;
    }
    return ans;
}
```

---

### **Complexity Analysis**

**Time Complexity:** `O(n + m)` – Similar to the difference array.

**Space Complexity:** `O(n)`.

## **Segment Tree (Not Needed but Valid)**

_(Only for completeness; too heavy for this problem)_

### **Approach**

- Build a segment tree supporting **range add** operations.
- Apply lazy propagation.
- Extract final values by reading the tree.
- Overkill for this problem, but works in all constraints.

---

### **Code (Complete, Minimal, Lazy Propagation)**

_(Not recommended; difference array is the expected solution)_

```cpp
class Solution {
    vector<int> tree, lazy;
    int n;

    void update(int idx, int l, int r, int ql, int qr, int val) {
        if (lazy[idx] != 0) {
            tree[idx] += lazy[idx];
            if (l != r) {
                lazy[idx*2] += lazy[idx];
                lazy[idx*2+1] += lazy[idx];
            }
            lazy[idx] = 0;
        }
        if (r < ql || l > qr) return;
        if (ql <= l && r <= qr) {
            tree[idx] += val;
            if (l != r) {
                lazy[idx*2] += val;
                lazy[idx*2+1] += val;
            }
            return;
        }
        int mid = (l+r)/2;
        update(idx*2, l, mid, ql, qr, val);
        update(idx*2+1, mid+1, r, ql, qr, val);
    }

    void buildAns(int idx, int l, int r, vector<int> &ans) {
        if (lazy[idx] != 0) {
            tree[idx] += lazy[idx];
            if (l != r) {
                lazy[idx*2] += lazy[idx];
                lazy[idx*2+1] += lazy[idx];
            }
            lazy[idx] = 0;
        }
        if (l == r) {
            ans[l] = tree[idx];
            return;
        }
        int mid = (l+r)/2;
        buildAns(idx*2, l, mid, ans);
        buildAns(idx*2+1, mid+1, r, ans);
    }

public:
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        n = length;
        tree.assign(4*n, 0);
        lazy.assign(4*n, 0);

        for (auto &u : updates)
            update(1, 0, n-1, u[0], u[1], u[2]);

        vector<int> ans(n, 0);
        buildAns(1, 0, n-1, ans);
        return ans;
    }
};

int main() {
    int length = 5;
    vector<vector<int>> updates = {{1,3,2},{2,4,3},{0,2,-2}};
    Solution s1;
    vector<int> ans = s1.getModifiedArray(length, updates);
    for (int x : ans) cout << x << " ";
    return 0;
}
```

---

### **Complexity Analysis**

**Time Complexity:** `O(m log n)` – Each update hits O(log n).

**Space Complexity:** `O(n)` – Segment tree nodes.

---

THE END
