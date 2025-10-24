#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> shortestPath(int n, vector<vector<int>>& edges) {
        // Step 1: Build adjacency list
        vector<vector<int>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        // Step 2: Initialize distance array
        const int INF = 1e9;
        vector<int> dist(n, INF);
        dist[0] = 0;

        // Step 3: BFS traversal
        queue<int> q;
        q.push(0);

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int neighbor : adj[node]) {
                if (dist[neighbor] > dist[node] + 1) {
                    dist[neighbor] = dist[node] + 1;
                    q.push(neighbor);
                }
            }
        }

        // Step 4: Replace unreachable nodes with -1
        for (int& d : dist) {
            if (d == INF) d = -1;
        }

        return dist;
    }
};

int main() {
    int n = 6;
    vector<vector<int>> edges = {
        {0, 1}, {0, 2}, {1, 3}, {2, 4}, {4, 5}
    };

    Solution s;
    vector<int> res = s.shortestPath(n, edges);

    for (int d : res) cout << d << " ";
    return 0;
}