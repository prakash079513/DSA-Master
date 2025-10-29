#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> dijkstra(int V, vector<vector<pair<int,int>>> &adj, int src) {
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;

        set<pair<int,int>> st;
        st.insert({0, src});

        while (!st.empty()) {
            auto it = *(st.begin());
            int node = it.second;
            int d = it.first;
            st.erase(it);

            for (auto &edge : adj[node]) {
                int next = edge.first;
                int wt = edge.second;

                if (d + wt < dist[next]) {
                    if (dist[next] != INT_MAX)
                        st.erase({dist[next], next});

                    dist[next] = d + wt;
                    st.insert({dist[next], next});
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
