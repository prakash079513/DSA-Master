#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isCyclic(int V, vector<int> adj[]) {
        vector<int> indegree(V, 0);

        // Step 1: Compute indegree of each node
        for (int i = 0; i < V; i++) {
            for (auto it : adj[i]) {
                indegree[it]++;
            }
        }

        // Step 2: Push all 0 indegree nodes into queue
        queue<int> q;
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) q.push(i);
        }

        // Step 3: Perform BFS (Kahn’s Algorithm)
        int count = 0;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            count++;

            for (auto it : adj[node]) {
                indegree[it]--;
                if (indegree[it] == 0) q.push(it);
            }
        }

        // Step 4: If count != V, graph has a cycle
        return count != V;
    }
};

int main() {
    int V = 4;
    vector<int> adj[V];
    adj[0].push_back(1);
    adj[1].push_back(2);
    adj[2].push_back(3);
    adj[3].push_back(1); // Cycle

    Solution s;
    bool hasCycle = s.isCyclic(V, adj);
    cout << (hasCycle ? "Cycle detected" : "No cycle");
    return 0;
}
