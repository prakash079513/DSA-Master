#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int V = graph.size();
        vector<vector<int>> revGraph(V);
        vector<int> indegree(V, 0);

        // Reverse the graph
        for (int u = 0; u < V; u++) {
            for (auto v : graph[u]) {
                revGraph[v].push_back(u);
                indegree[u]++;
            }
        }

        queue<int> q;
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) q.push(i);
        }

        vector<int> safe;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            safe.push_back(node);

            for (auto neigh : revGraph[node]) {
                indegree[neigh]--;
                if (indegree[neigh] == 0) q.push(neigh);
            }
        }

        sort(safe.begin(), safe.end());
        return safe;
    }
};

int main() {
    vector<vector<int>> graph = {{1,2},{2,3},{5},{0},{5},{},{}};
    Solution s;
    vector<int> ans = s.eventualSafeNodes(graph);
    for (int node : ans) cout << node << " ";
    return 0;
}