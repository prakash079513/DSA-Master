#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void topoDFS(int node, vector<pair<int,int>> adj[], vector<int> &vis, stack<int> &st) {
        vis[node] = 1;
        for (auto it : adj[node]) {
            int v = it.first;
            if (!vis[v]) topoDFS(v, adj, vis, st);
        }
        st.push(node);
    }

    vector<int> shortestPath(int N, int M, vector<vector<int>> &edges) {
        vector<pair<int,int>> adj[N]; // Take vector of pairs.
        for (int i = 0; i < M; i++) { // Note: Till M only. Do not forget.
            int u = edges[i][0], v = edges[i][1], w = edges[i][2];
            adj[u].push_back({v, w});
        }

        vector<int> vis(N, 0);
        stack<int> st;
        for (int i = 0; i < N; i++) {
            if (!vis[i]) topoDFS(i, adj, vis, st);
        }

        vector<int> dist(N, 1e9);
        dist[0] = 0; // Note: Initialize the source. Do not forget.

        while (!st.empty()) {
            int node = st.top();
            st.pop();

            if (dist[node] != 1e9) {
                for (auto it : adj[node]) {
                    int v = it.first, w = it.second;
                    if (dist[node] + w < dist[v]) {
                        dist[v] = dist[node] + w;
                    }
                }
            }
        }
        return dist;
    }
};

int main() {
    int N = 6, M = 7;
    vector<vector<int>> edges = {{0,1,2},{0,4,1},{4,5,4},{4,2,2},{1,2,3},{2,3,6},{5,3,1}};
    Solution s;
    vector<int> res = s.shortestPath(N, M, edges);
    for (int x : res) cout << (x == 1e9 ? -1 : x) << " ";
    return 0;
}