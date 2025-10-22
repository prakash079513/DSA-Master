#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string findOrder(string dict[], int N, int K) {
        vector<vector<int>> adj(K);

        // Step 1: Build the graph
        for (int i = 0; i < N - 1; i++) {
            string s1 = dict[i];
            string s2 = dict[i + 1];
            int len = min(s1.size(), s2.size());

            for (int j = 0; j < len; j++) {
                if (s1[j] != s2[j]) {
                    adj[s1[j] - 'a'].push_back(s2[j] - 'a');
                    break;
                }
            }
        }

        // Step 2: Compute indegree
        vector<int> indegree(K, 0);
        for (int i = 0; i < K; i++) {
            for (auto it : adj[i]) indegree[it]++;
        }

        // Step 3: Kahn's Algorithm
        queue<int> q;
        for (int i = 0; i < K; i++) {
            if (indegree[i] == 0) q.push(i);
        }

        string order = "";
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            order += (char)(node + 'a');

            for (auto neigh : adj[node]) {
                indegree[neigh]--;
                if (indegree[neigh] == 0) q.push(neigh);
            }
        }

        return order;
    }
};

int main() {
    int N = 5, K = 4;
    string dict[] = {"baa", "abcd", "abca", "cab", "cad"};
    Solution s;
    cout << s.findOrder(dict, N, K);
    return 0;
}