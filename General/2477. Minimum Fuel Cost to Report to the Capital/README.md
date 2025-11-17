# Minimum Fuel to Bring All People to the Source Node

Author: [Prakash JC](https://prakash079513.github.io)

[Leetcode 2477](https://leetcode.com/problems/minimum-fuel-cost-to-report-to-the-capital/description/)

## Problem Statement

You are given an undirected tree with `n` nodes (labeled `0` to `n−1`) and exactly `n−1` edges.

Each node contains **exactly one person** and **exactly one car**.

Each car has a **capacity `c`** (maximum number of persons it can carry).

All persons must travel to **source node 0**.

Travel rules:

1. A car can move along an edge by spending **1 litre of fuel**.
2. A car may pick up people along the way, but **cannot exceed capacity c**.
3. Multiple cars can move independently; fuel consumed is the sum of all their movements.
4. People can change cars at intermediate nodes (same as LC rules).
5. Goal: **Minimize total fuel consumed by all cars**.

### Example

Edges:

0-1, 0-4, 0-5, 1-3, 3-2, 4-6

Capacity: `c = 2`

Minimum fuel = **7 litres**

---

### Intuition

This is a **tree DP / DFS aggregation** problem.

Key insight:

Every node (except root) must send its people **upward toward the root**, moving through exactly one parent edge.

For each subtree, we count:

- how many total people are in the subtree,
- how many cars are needed to move them upward.

### Why cars needed = `ceil(people / c)`?

Each car has capacity `c`.

People from a subtree must go through the unique parent edge.

If a subtree has `x` people, the minimum number of car trips is:

`trips = (x + c - 1) / c`

Each trip consumes **1 litre**, because it crosses one edge.

### Total fuel

For every edge `(parent, child)`

Fuel += number of trips needed to move child-subtree people upward.

We accumulate contributions bottom-up.

## Expected Approach (DFS Aggregation)

1. Build adjacency list for the tree.
2. Run DFS from source node `0`.
3. For each node:
   - Calculate number of people in its subtree.
   - Ignore the root when calculating fuel.
4. For each child → parent return:
   - `people_in_subtree[child]`
   - trips = `ceil(people / c)`
   - add trips to total fuel.

Return total fuel.

This gives the optimal answer because:

- All nodes are leaves of some subtree.
- Each subtree’s people must cross the parent edge exactly once.
- We simply minimize car-moves by grouping up to `c` people in one trip.

---

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long fuel = 0;
    int capacity;

    int dfs(int node, int parent, vector<vector<int>> &adj) {
        int people = 1; // one person at this node

        for (int nei : adj[node]) {
            if (nei == parent) continue;
            int sub = dfs(nei, node, adj);

            long long trips = (sub + capacity - 1) / capacity;
            fuel += trips;  // cost to move subtree people to this node

            people += sub;
        }
        return people;
    }

    long long minimumFuelCost(int n, vector<vector<int>> &edges, int c) {
        capacity = c;

        vector<vector<int>> adj(n);
        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        dfs(0, -1, adj);
        return fuel;
    }
};

int main() {
    int n = 7;
    vector<vector<int>> edges = {
        {0,1}, {0,4}, {0,5}, {1,3}, {3,2}, {4,6}
    };
    int c = 2;

    Solution s;
    cout << s.minimumFuelCost(n, edges, c);
    return 0;
}
```

---

### Complexity Analysis

**Time Complexity:** `O(n)` – DFS visits each node exactly once.

**Space Complexity:** `O(n)` – adjacency list + recursion stack.

---

THE END
