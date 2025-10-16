#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool bfsCheck(int start, vector<vector<int>>& adj, vector<int>& color) {
        queue<int> q;
        q.push(start);
        color[start] = 0;  // Start coloring with 0

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (auto neighbor : adj[node]) {
                // If neighbor not colored, color with opposite color
                if (color[neighbor] == -1) {
                    color[neighbor] = 1 - color[node];
                    q.push(neighbor);
                }
                // If neighbor has same color, not bipartite
                else if (color[neighbor] == color[node]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool isBipartite(vector<vector<int>>& adj) {
        int V = adj.size();
        vector<int> color(V, -1);  // -1 means uncolored

        for (int i = 0; i < V; i++) {
            if (color[i] == -1) {
                if (!bfsCheck(i, adj, color))
                    return false;
            }
        }
        return true;
    }
};

int main() {
    vector<vector<int>> adj = {
        {1, 3},
        {0, 2},
        {1, 3},
        {0, 2}
    };

    Solution s;
    cout << (s.isBipartite(adj) ? "Yes" : "No");
    return 0;
}