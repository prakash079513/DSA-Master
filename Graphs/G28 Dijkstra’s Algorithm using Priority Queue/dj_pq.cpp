#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> dijkstra(int V, vector<vector<pair<int,int>>> &adj, int src) {
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;

        priority_queue<pair<int,int>, vector<pair<int,int>>,
                       greater<pair<int,int>>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [d, node] = pq.top();
            pq.pop();

            if (d > dist[node]) continue;

            for (auto &it : adj[node]) {
                int next = it.first;
                int wt = it.second;

                if (d + wt < dist[next]) {
                    dist[next] = d + wt;
                    pq.push({dist[next], next});
                }
            }
        }
        return dist;
    }
};

int main() {
    int V = 5;
    vector<vector<pair<int,int>>> adj(V);
    adj[0].push_back({1, 2});
    adj[1].push_back({2, 3});
    adj[0].push_back({3, 6});
    adj[3].push_back({1, 2});
    adj[2].push_back({4, 5});
    adj[1].push_back({4, 1});

    Solution s;
    vector<int> dist = s.dijkstra(V, adj, 0);

    for (int d : dist) cout << d << " ";
    return 0;
}
