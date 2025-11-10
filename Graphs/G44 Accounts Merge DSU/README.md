# Accounts Merge — DSU

Author: [Prakash JC](https://prakash079513.github.io/)

## Problem Statement

You are given a list of **accounts**, where each account represents a person’s name and the list of emails they own.

Each account `accounts[i]` is of the form `[name, email1, email2, ...]`.

Two accounts **belong to the same person** if they share **at least one common email**.

Even if two accounts have the same name, they may belong to **different people**.

Your task is to **merge** all the accounts belonging to the same person and return them in the format:

- First element → Name
- Remaining elements → Sorted list of unique emails.

---

### Example

```
Input:
accounts = [
  ["John","johnsmith@mail.com","john_newyork@mail.com"],
  ["John","johnsmith@mail.com","john00@mail.com"],
  ["Mary","mary@mail.com"],
  ["John","johnnybravo@mail.com"]
]

Output:
[
  ["John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"],
  ["Mary","mary@mail.com"],
  ["John","johnnybravo@mail.com"]
]
```

**Explanation:**

- The first two accounts belong to the same John because they share `johnsmith@mail.com`.
- The other two remain separate.

---

### Intuition

- Each **account** can be seen as a **node**.
- If two accounts share an **email**, they should be **merged** (connected).
- So we use **Disjoint Set Union (DSU)** to connect all accounts that share common emails.
- After union operations, accounts with the **same ultimate parent** belong to the same person.

---

### Approach

1. **Create a DSU** of size `n` (number of accounts).
2. **Map each email** to the account index that owns it:
   - If an email is already mapped, union the current account with the one already mapped.
3. **Group emails** by their ultimate parent (found via DSU).
4. **Sort** the emails for each group and prepend the person’s name.
5. Return the final merged list.

---

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
public:
    vector<int> parent, size;
    DisjointSet(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int findUPar(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findUPar(parent[node]);
    }

    void unionBySize(int u, int v) {
        int pu = findUPar(u), pv = findUPar(v);
        if (pu == pv) return;
        if (size[pu] < size[pv]) {
            parent[pu] = pv;
            size[pv] += size[pu];
        } else {
            parent[pv] = pu;
            size[pu] += size[pv];
        }
    }
};

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        DisjointSet ds(n);
        unordered_map<string, int> mailToNode;

        // Step 1: Map emails and union related accounts
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < accounts[i].size(); j++) {
                string mail = accounts[i][j];
                if (mailToNode.find(mail) == mailToNode.end())
                    mailToNode[mail] = i;
                else
                    ds.unionBySize(i, mailToNode[mail]);
            }
        }

        // Step 2: Group emails by their ultimate parent
        vector<vector<string>> mergedMails(n);
        for (auto &it : mailToNode) {
            string mail = it.first;
            int node = ds.findUPar(it.second);
            mergedMails[node].push_back(mail);
        }

        // Step 3: Build final answer
        vector<vector<string>> ans;
        for (int i = 0; i < n; i++) {
            if (mergedMails[i].empty()) continue;
            sort(mergedMails[i].begin(), mergedMails[i].end());
            vector<string> curr;
            curr.push_back(accounts[i][0]); // name
            for (auto &mail : mergedMails[i]) curr.push_back(mail);
            ans.push_back(curr);
        }

        return ans;
    }
};

int main() {
    vector<vector<string>> accounts = {
        {"John","johnsmith@mail.com","john_newyork@mail.com"},
        {"John","johnsmith@mail.com","john00@mail.com"},
        {"Mary","mary@mail.com"},
        {"John","johnnybravo@mail.com"}
    };
    Solution s1;
    auto res = s1.accountsMerge(accounts);
    for (auto &v : res) {
        for (auto &s : v) cout << s << " ";
        cout << endl;
    }
    return 0;
}
```

---

### Complexity Analysis

**Time Complexity:** `O(N * K * α(N))`

- Each union/find takes nearly constant time (`α(N)`),
- Sorting emails adds an additional factor for groups, so total is dominated by merging.

**Space Complexity:** `O(N * K)`

- For DSU arrays, hash map, and storing all emails.

---

THE END
