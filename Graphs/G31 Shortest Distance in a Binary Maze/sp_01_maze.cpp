#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int shortestPath(vector<vector<int>> &grid, pair<int,int> source, pair<int,int> destination) {
        int n = grid.size(), m = grid[0].size();
        if (grid[source.first][source.second] == 0 || grid[destination.first][destination.second] == 0)
            return -1;

        vector<vector<int>> dist(n, vector<int>(m, 1e9));
        dist[source.first][source.second] = 0;

        queue<pair<int, pair<int,int>>> q;
        q.push({0, {source.first, source.second}});

        int dRow[] = {-1, 0, 1, 0};
        int dCol[] = {0, 1, 0, -1};

        while (!q.empty()) {
            auto it = q.front();
            q.pop();
            int d = it.first;
            int r = it.second.first;
            int c = it.second.second;

            if (r == destination.first && c == destination.second)
                return d;

            for (int i = 0; i < 4; i++) {
                int nr = r + dRow[i];
                int nc = c + dCol[i];
                if (nr >= 0 && nc >= 0 && nr < n && nc < m && grid[nr][nc] == 1 && d + 1 < dist[nr][nc]) {
                    dist[nr][nc] = d + 1;
                    q.push({d + 1, {nr, nc}});
                }
            }
        }
        return -1;
    }
};

int main() {
    vector<vector<int>> grid = {
        {1, 0, 0},
        {1, 1, 0},
        {0, 1, 1}
    };
    pair<int,int> source = {0, 0};
    pair<int,int> destination = {2, 2};
    Solution s;
    cout << s.shortestPath(grid, source, destination);
    return 0;
}
