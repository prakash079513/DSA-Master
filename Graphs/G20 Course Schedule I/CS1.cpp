#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> adj[numCourses];
        vector<int> indegree(numCourses, 0);

        // Build adjacency list and indegree array
        for (auto it : prerequisites) {
            adj[it[1]].push_back(it[0]);
            indegree[it[0]]++;
        }

        queue<int> q;
        // Push courses with no prerequisites
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) q.push(i);
        }

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

        return count == numCourses;
    }
};

int main() {
    int numCourses = 4;
    vector<vector<int>> prerequisites = {{1,0},{2,1},{3,2}};
    Solution s;
    cout << (s.canFinish(numCourses, prerequisites) ? "Yes" : "No");
    return 0;
}