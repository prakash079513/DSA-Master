#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool checkForCycle(int src, vector<int> adj[], vector<int> &visited) {
        queue<pair<int, int>> q; // {node, parent}
        visited[src] = 1;
        q.push({src, -1});

        while (!q.empty()) {
            int node = q.front().first;
            int parent = q.front().second;
            q.pop();

            for (auto neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = 1;
                    q.push({neighbor, node});
                }
                // If already visited and not parent → cycle
                else if (neighbor != parent) {
                    return true;
                }
            }
        }
        return false;
    }

    bool isCycle(int V, vector<int> adj[]) {
        vector<int> visited(V, 0);

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                if (checkForCycle(i, adj, visited)) return true;
            }
        }
        return false;
    }
};

int main() {
    int V = 5;
    vector<int> adj[V];
    adj[0] = {1};
    adj[1] = {0, 2, 4};
    adj[2] = {1, 3};
    adj[3] = {2, 4};
    adj[4] = {1, 3};

    Solution s1;
    cout << (s1.isCycle(V, adj) ? "Cycle Detected" : "No Cycle");
    return 0;
}