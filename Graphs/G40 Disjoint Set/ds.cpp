#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
public:
    vector<int> rank, parent, size;

    // Constructor
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        size.resize(n + 1, 1);   // size initialized to 1
        parent.resize(n + 1);
        for (int i = 0; i <= n; i++)
            parent[i] = i;
    }

    // Find with path compression
    int findParent(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findParent(parent[node]);
    }

    // Union by Rank
    void unionByRank(int u, int v) {
        int pu = findParent(u);
        int pv = findParent(v);
        if (pu == pv) return; // already in same set

        if (rank[pu] < rank[pv]) parent[pu] = pv;
        else if (rank[pv] < rank[pu]) parent[pv] = pu;
        else {
            parent[pv] = pu;
            rank[pu]++;
        }
    }

    // Union by Size
    void unionBySize(int u, int v) {
        int pu = findParent(u);
        int pv = findParent(v);
        if (pu == pv) return; // already in same set

        if (size[pu] < size[pv]) {
            parent[pu] = pv;
            size[pv] += size[pu];
        } else {
            parent[pv] = pu;
            size[pu] += size[pv];
        }
    }
};

int main() {
    DisjointSet ds(7);

    // Using union by rank
    ds.unionByRank(1, 2);
    ds.unionByRank(2, 3);
    ds.unionByRank(4, 5);
    ds.unionByRank(6, 7);
    ds.unionByRank(5, 6);

    cout << (ds.findParent(3) == ds.findParent(7) ? "Same Component" : "Different Components") << endl;

    ds.unionByRank(3, 7);
    cout << (ds.findParent(3) == ds.findParent(7) ? "Same Component" : "Different Components") << endl;

    // Using union by size (example)
    DisjointSet ds2(7);
    ds2.unionBySize(1, 2);
    ds2.unionBySize(2, 3);
    ds2.unionBySize(4, 5);
    ds2.unionBySize(6, 7);
    ds2.unionBySize(5, 6);
    ds2.unionBySize(3, 7);

    cout << (ds2.findParent(3) == ds2.findParent(7) ? "Same Component (Size)" : "Different Components (Size)") << endl;

    return 0;
}
