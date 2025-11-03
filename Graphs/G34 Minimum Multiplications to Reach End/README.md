# Minimum Multiplications to Reach End

**Author:** [Prakash JC](https://prakash079513.github.io/)

## Problem Statement

You are given integers `start`, `end`, and an array `arr` of size `n`.

In one step, you can multiply `start` by **any element** in `arr` and take the result modulo `100000`.

Find the **minimum number of multiplications** required to reach `end` from `start`.

If it’s not possible, return `-1`.

**Example:**

Input: `arr = {2, 5, 7}`, `start = 3`, `end = 30`

Output: `2`

Explanation:

`3 * 2 = 6`, `6 * 5 = 30`, reached in 2 steps.

---

### Intuition

- Each number from `0` to `99999` can be treated as a **node in a graph**.
- An edge exists from node `x` to `(x * a) % 100000` for every `a` in `arr`.
- We need the **minimum number of edges** from `start` to `end`, so **BFS** is ideal.

---

### Approach

- Use BFS where each state represents the current number.
- Maintain a `dist[]` array storing the minimum steps to reach each number.
- Push the initial state `(start, 0)` into the queue.
- For every multiplication with elements in `arr`, compute `(num * a) % 100000`.
- If a new number gives a shorter distance, update and push to the queue.
- Return `dist[end]` if reachable, else `1`.

---

### Code

```cpp
int minimumMultiplications(vector<int>& arr, int start, int end) {
    vector<int> dist(100000, INT_MAX);
    queue<pair<int, int>> q;

    dist[start] = 0;
    q.push({start, 0});

    while (!q.empty()) {
        auto [num, steps] = q.front();
        q.pop();

        for (int mul : arr) {
            int next = (num * mul) % 100000;
            if (steps + 1 < dist[next]) {
                dist[next] = steps + 1;
                if (next == end) return steps + 1;
                q.push({next, steps + 1});
            }
        }
    }

    return -1;
}
```

### Complexity Analysis

**Time Complexity:** `O(100000 * n)` — in the worst case, each of 100000 nodes may be processed once for all `n` multipliers.

**Space Complexity:** `O(100000)` — for the distance array and BFS queue.

---

THE END
