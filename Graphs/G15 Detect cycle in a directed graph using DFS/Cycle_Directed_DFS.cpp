#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool dfs(int node, vector<vector<int>>& adj, vector<int>& state) {
        state[node] = 1; // visiting

        for (auto neighbor : adj[node]) {
            if (state[neighbor] == 0) {
                if (dfs(neighbor, adj, state))
                    return true;
            }
            else if (state[neighbor] == 1) {
                return true; // back edge found
            }
        }

        state[node] = 2; // processed
        return false;
    }

    bool isCyclic(int V, vector<vector<int>>& adj) {
        vector<int> state(V, 0); // 0 - unvisited, 1 - visiting, 2 - processed

        for (int i = 0; i < V; i++) {
            if (state[i] == 0) {
                if (dfs(i, adj, state))
                    return true;
            }
        }
        return false;
    }
};

int main() {
    vector<vector<int>> adj = {
        {1}, {2}, {3}, {1}
    };

    Solution s;
    cout << (s.isCyclic(4, adj) ? "Cycle Detected" : "No Cycle");
    return 0;
}