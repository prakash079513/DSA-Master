#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> shortestPath(int V, int E, vector<vector<int>> &edges) {
        vector<pair<int,int>> adj[V+1];
        for (auto &e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
            adj[e[1]].push_back({e[0], e[2]});
        }

        vector<int> dist(V+1, 1e9), parent(V+1);
        for (int i = 1; i <= V; i++) parent[i] = i;

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        dist[1] = 0;
        pq.push({0, 1});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            for (auto [v, wt] : adj[u]) {
                if (d + wt < dist[v]) {
                    dist[v] = d + wt;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        if (dist[V] == 1e9) return {-1};

        vector<int> path;
        int node = V;
        while (parent[node] != node) {
            path.push_back(node);
            node = parent[node];
        }
        path.push_back(1);
        reverse(path.begin(), path.end());
        return path;
    }
};

int main() {
    int V = 5, E = 6;
    vector<vector<int>> edges = {{1,2,2}, {2,5,5}, {2,3,4}, {1,4,1}, {4,3,3}, {3,5,1}};
    Solution s;
    vector<int> path = s.shortestPath(V, E, edges);
    for (int x : path) cout << x << " ";
    return 0;
}