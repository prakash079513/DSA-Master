#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
    vector<int> parent, size;
public:
    DisjointSet(int n) {
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        for (int i = 0; i <= n; i++) parent[i] = i;
    }

    int findParent(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findParent(parent[node]); // Path compression
    }

    void unionBySize(int u, int v) {
        int pu = findParent(u);
        int pv = findParent(v);
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
    int spanningTree(int n, vector<vector<int>> &edges) {
        vector<pair<int, pair<int, int>>> edgeList;
        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            edgeList.push_back({w, {u, v}});
        }

        sort(edgeList.begin(), edgeList.end());
        DisjointSet ds(n);
        int mstWeight = 0;

        for (auto &it : edgeList) {
            int w = it.first;
            int u = it.second.first;
            int v = it.second.second;

            if (ds.findParent(u) != ds.findParent(v)) {
                mstWeight += w;
                ds.unionBySize(u, v);
            }
        }

        return mstWeight;
    }
};

int main() {
    int n = 5;
    vector<vector<int>> edges = {
        {0, 1, 2}, {0, 3, 6}, {1, 3, 8}, {1, 2, 3}, {1, 4, 5}, {2, 4, 7}
    };
    Solution obj;
    cout << "MST Weight: " << obj.spanningTree(n, edges) << endl;
    return 0;
}