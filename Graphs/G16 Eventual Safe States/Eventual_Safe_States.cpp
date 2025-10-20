#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool dfs(int node, vector<int> adj[], vector<int>& vis) {
        vis[node] = 1; // node in current path
        for (auto it : adj[node]) {
            if (vis[it] == 0) {
                if (dfs(it, adj, vis)) return true; // cycle found
            }
            else if (vis[it] == 1) return true; // back edge → cycle
        }
        vis[node] = 2; // safe node
        return false;  // no cycle found
    }

    vector<int> eventualSafeNodes(int V, vector<int> adj[]) {
        vector<int> vis(V, 0);
        for (int i = 0; i < V; i++) {
            if (vis[i] == 0) dfs(i, adj, vis);
        }

        vector<int> safe;
        for (int i = 0; i < V; i++) {
            if (vis[i] == 2) safe.push_back(i);
        }
        return safe;
    }
};

int main() {
    int V = 7;
    vector<int> adj[V] = {
        {1,2}, {2,3}, {5}, {0}, {5}, {}, {}
    };
    Solution s;
    vector<int> ans = s.eventualSafeNodes(V, adj);
    for (int x : ans) cout << x << " ";
    return 0;
}