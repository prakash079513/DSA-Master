#include <bits/stdc++.h>
using namespace std;

class Solution {
public: 
    vector<int> bfs(int V, vector<vector<int>> &adj[]){
        vector<int> bfs;
        vector<int> visited(V);
        queue<int> q;

        q.push(0);
        visited[0] = 1;

        while(!q.empty()){
            int node = q.front();
            q.pop();
            bfs.push_back(node);

            for(int n : adj[node]){
                if(!visited[n]) {
                    q.push(n);
                    visited[n] = 1;   
                }
            }
        }
        return bfs;
    }

    //////////////////////////////////////////////////////////////////////////////////////

    void dfsHelper(int node, vector<int> adj[], vector<int> &visited, vector<int> &dfs) {
        visited[node] = 1;
        dfs.push_back(node);

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfsHelper(neighbor, adj, visited, dfs);
            }
        }
    }

    vector<int> dfs(int V, vector<int> adj[]) {
        vector<int> ans;
        vector<int> visited(V, 0);

        dfsHelper(0, adj, visited, dfs); // start from node 0
        return ans;
    }


    vector<int> dfsDisconnected(int V, vector<int> adj[]) {
        vector<int> dfs;
        vector<int> visited(V, 0);

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfsHelper(i, adj, visited, dfs);
            }
        }
        return dfs;
    }
    
    //////////////////////////////////////////////////////////////////////////////////////
    // DFS using stack

    void dfsIterative(int V, vector<int> adj[]) {
        vector<int> dfs;
        vector<int> visited(V);
        stack<int> st;

        st.push(0);
        
        while(!st.empty()){
            int node = st.top();
            st.pop();

            if(!visited[node]){
                visited[node] = 1;
                dfs.push_back(node);

                for(auto it = adj[node].rbegin(); it != adj[node].rend(); it++){
                    if(!visited[*it]) st.push(*it);
                }
            }
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////
    // no of provinces using bfs:

    int nop(vector<vector<int>> &isConnected) {
        int n = isConnected.size();
        vector<int> visited(n, 0);
        int provinces = 0;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                provinces++;
                queue<int> q;
                q.push(i);
                visited[i] = 1;

                while (!q.empty()) {
                    int node = q.front();
                    q.pop();

                    for (int j = 0; j < n; j++) {
                        if (isConnected[node][j] == 1 && !visited[j]) {
                            q.push(j);
                            visited[j] = 1;
                        }
                    }
                }
            }
        }
        return provinces;
    }

    //////////////////////////////////////////////////////////////////////////////////////

    // no of provinces using dfs:

    void dfs(int node, vector<vector<int>> &isConnected, vector<int> &visited, int n) {
        visited[node] = 1;
        for (int j = 0; j < n; j++) {
            if (isConnected[node][j] == 1 && !visited[j]) {
                dfs(j, isConnected, visited, n);
            }
        }
    }

    int nop(vector<vector<int>> &isConnected) {
        int n = isConnected.size();
        vector<int> visited(n, 0);
        int provinces = 0;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                provinces++;
                dfs(i, isConnected, visited, n);
            }
        }
        return provinces;
    }

    //////////////////////////////////////////////////////////////////////////////////////
    
    // Number of Islands using dfs
    // Given a 2d matrix with a region of 1s. Count them.

    void dfs(int row, int col, vector<vector<int>> &visited, vector<vector<int>> &grid) {
        int n = grid.size();
        int m = grid[0].size();
        visited[row][col] = 1;

        // 8 directions
        for(int dr = -1; dr <= 1; dr++) {
            for(int dc = -1; dc <= 1; dc++) {
                int rn = row + dr;
                int cn = col + dc;
                if(rn >= 0 && rn < n && cn >= 0 && cn < m 
                   && grid[rn][cn] == 1 && !visited[rn][cn]) {
                    dfs(rn, cn, visited, grid);
                }
            }
        }
    }

    int numIslands(vector<vector<int>> &grid) {
        int n = grid.size();
        int m = grid[0].size();
        int islands = 0;
        vector<vector<int>> visited(n, vector<int>(m, 0));

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(grid[i][j] == 1 && !visited[i][j]) {
                    islands++;
                    dfs(i, j, visited, grid);
                }
            }
        }
        return islands;
    }

    //////////////////////////////////////////////////////////////////////////////////////

    // Flood Fill Algorithm
    // Given a grid, starting index, a new color, go news direction, fill with the new color. 

    // using dfs:

    void dfs(int row, int col, vector<vector<int>> &image, int newColor, int initColor) {
        int n = image.size();
        int m = image[0].size();
        image[row][col] = newColor;

        int delRow[] = {-1, 0, 1, 0};
        int delCol[] = {0, 1, 0, -1};

        for (int i = 0; i < 4; i++) {
            int r = row + delRow[i];
            int c = col + delCol[i];
            if (r >= 0 && r < n && c >= 0 && c < m && image[r][c] == initColor) {
                dfs(r, c, image, newColor, initColor);
            }
        }
    }

    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int newColor) {
        int initColor = image[sr][sc];
        if (initColor == newColor) return image;  // no need to fill

        dfs(sr, sc, image, newColor, initColor);
        return image;
    }

    //////////////////////////////////////////////////////////////////////////////////////

    // Rotten Oranges
    // Recommended approach: BFS

    int orangesRotting(vector<vector<int>> &grid) {
        int n = grid.size();
        int m = grid[0].size();

        queue<pair<pair<int, int>, int>> q; // ((row, col), time)
        int freshCount = 0;

        // Push all initially rotten oranges into queue
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 2) {
                    q.push({{i, j}, 0});
                } else if (grid[i][j] == 1) {
                    freshCount++;
                }
            }
        }

        int time = 0;
        int delRow[] = {-1, 0, 1, 0};
        int delCol[] = {0, 1, 0, -1};
        int madeRotten = 0;

        // Perform BFS
        while (!q.empty()) {
            int r = q.front().first.first;
            int c = q.front().first.second;
            int t = q.front().second;
            q.pop();

            time = max(time, t);

            for (int i = 0; i < 4; i++) {
                int rn = r + delRow[i];
                int cn = c + delCol[i];

                if (rn >= 0 && rn < n && cn >= 0 && cn < m && grid[rn][cn] == 1) {
                    grid[rn][cn] = 2;
                    madeRotten++;
                    q.push({{rn, cn}, t + 1});
                }
            }
        }

        // Check if all fresh oranges became rotten
        if (rottenCount != freshCount) return -1;
        return time;
    }

    //////////////////////////////////////////////////////////////////////////////////////

    // Detect Cycle in an Undirected Graph
    // Using BFS

    bool checkForCycle(int src, vector<int> adj[], vector<int> &visited) {
        queue<pair<int, int>> q; // {node, parent}
        q.push({src, -1});
        visited[src] = 1;

        while (!q.empty()) {
            int node = q.front().first;
            int parent = q.front().second;
            q.pop();

            for (auto nei: adj[node]) {
                if (!visited[nei]) {
                    q.push({nei, node});
                    visited[nei] = 1;
                } 
                // If already visited and not parent → cycle
                else if (nei != parent) {
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

    //////////////////////////////////////////////////////////////////////////////////////
    // Cycle detection using DFS

    bool dfs(int node, int parent, vector<int> adj[], vector<int> &visited) {
        visited[node] = 1;

        for (auto neighbor : adj[node]) {
            if (!visited[neighbor]) {
                if (dfs(neighbor, node, adj, visited)) return true;
            } 
            else if (neighbor != parent) {
                return true;
            }
        }
        return false;
    }

    bool isCycle(int V, vector<int> adj[]) {
        vector<int> visited(V, 0);

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                if (dfs(i, -1, adj, visited)) return true;
            }
        }
        return false;
    }

    //////////////////////////////////////////////////////////////////////////////////////
    // Nearest 1 in Binary Grid
    // Recommended: BFS

    vector<vector<int>> nearest(vector<vector<int>> grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> dist(n, vector<int>(m, -1));
        queue<pair<int, int>> q;

        // Step 1: Push all cells with 1
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    dist[i][j] = 0;
                    q.push({i, j});
                }
            }
        }

        // Directions for up, right, down, left
        int dr[] = {-1, 0, 1, 0};
        int dc[] = {0, 1, 0, -1};

        // Step 2: BFS
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i], nc = c + dc[i];
                if (nr >= 0 && nr < n && nc >= 0 && nc < m && dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1; // old row dist + 1
                    q.push({nr, nc});
                }
            }
        }

        return dist;
    }

    //////////////////////////////////////////////////////////////////////////////////////
    
    // Replace 'O's with 'X's
    // Recommended: DFS

    void dfs(int r, int c, vector<vector<char>> &mat, vector<vector<int>> &vis, int n, int m) {
        vis[r][c] = 1;

        int dr[] = {-1, 0, 1, 0};
        int dc[] = {0, 1, 0, -1};

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr >= 0 && nr < n && nc >= 0 && nc < m && !vis[nr][nc] && mat[nr][nc] == 'O') {
                dfs(nr, nc, mat, vis, n, m);
            }
        }
    }

    vector<vector<char>> fill(int n, int m, vector<vector<char>> mat) {
        vector<vector<int>> vis(n, vector<int>(m, 0));

        // Step 1: Mark all boundary-connected 'O's as safe
        for (int j = 0; j < m; j++) {
            if (mat[0][j] == 'O' && !vis[0][j]) dfs(0, j, mat, vis, n, m);
            if (mat[n-1][j] == 'O' && !vis[n-1][j]) dfs(n-1, j, mat, vis, n, m);
        }
        for (int i = 0; i < n; i++) {
            if (mat[i][0] == 'O' && !vis[i][0]) dfs(i, 0, mat, vis, n, m);
            if (mat[i][m-1] == 'O' && !vis[i][m-1]) dfs(i, m-1, mat, vis, n, m);
        }

        // Step 2: Convert unvisited 'O's to 'X' and visited 'O's stay as 'O'
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!vis[i][j] && mat[i][j] == 'O')
                    mat[i][j] = 'X';
            }
        }

        return mat;
    }

    //////////////////////////////////////////////////////////////////////////////////////
    
    // Number of Enclaves 
    // Recommended: BFS

    void bfs(int r, int c, vector<vector<int>> &grid, vector<vector<int>> &vis, int n, int m) {
        queue<pair<int,int>> q;
        q.push({r, c});
        vis[r][c] = 1;

        int dr[] = {-1, 0, 1, 0};
        int dc[] = {0, 1, 0, -1};

        while (!q.empty()) {
            auto [row, col] = q.front();
            q.pop();

            for (int i = 0; i < 4; i++) {
                int nr = row + dr[i];
                int nc = col + dc[i];
                if (nr >= 0 && nr < n && nc >= 0 && nc < m && 
                    !vis[nr][nc] && grid[nr][nc] == 1) {
                    vis[nr][nc] = 1;
                    q.push({nr, nc});
                }
            }
        }
    }

    int numEnclaves(vector<vector<int>> &grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> vis(n, vector<int>(m, 0));

        for (int j = 0; j < m; j++) {
            if (grid[0][j] == 1 && !vis[0][j]) bfs(0, j, grid, vis, n, m);
            if (grid[n-1][j] == 1 && !vis[n-1][j]) bfs(n-1, j, grid, vis, n, m);
        }
        for (int i = 0; i < n; i++) {
            if (grid[i][0] == 1 && !vis[i][0]) bfs(i, 0, grid, vis, n, m);
            if (grid[i][m-1] == 1 && !vis[i][m-1]) bfs(i, m-1, grid, vis, n, m);
        }

        int enclaves = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1 && !vis[i][j])
                    enclaves++;
            }
        }

        return enclaves;
    }

    //////////////////////////////////////////////////////////////////////////////////////

    // Number of distinct islands
    // Recommended: DFS

    void dfs(int r, int c, vector<vector<int>>& grid, vector<vector<int>>& vis,
        vector<pair<int, int>>& shape, int baseR, int baseC) {
        int n = grid.size();
        int m = grid[0].size();
        vis[r][c] = 1;
        shape.push_back({r - baseR, c - baseC});

        int dr[] = {-1, 0, 1, 0};
        int dc[] = {0, 1, 0, -1};

        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];
            if (nr >= 0 && nr < n && nc >= 0 && nc < m &&
                !vis[nr][nc] && grid[nr][nc] == 1) {
                dfs(nr, nc, grid, vis, shape, baseR, baseC);
            }
        }
    }

    int countDistinctIslands(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> vis(n, vector<int>(m, 0));
        set<vector<pair<int, int>>> shapes;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!vis[i][j] && grid[i][j] == 1) {
                    vector<pair<int, int>> shape;
                    dfs(i, j, grid, vis, shape, i, j);
                    shapes.insert(shape);
                }
            }
        }
        return shapes.size();
    }

    //////////////////////////////////////////////////////////////////////////////////////

    // Bipartite Graph 
    // Recommended: Both

    bool bfsCheck(int start, vector<vector<int>>& adj, vector<int>& color) {
        queue<int> q;
        q.push(start);
        color[start] = 0;  // Start coloring with 0

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (auto neighbor : adj[node]) {
                // If neighbor not colored, color with opposite color
                if (color[neighbor] == -1) {
                    color[neighbor] = 1 - color[node];
                    q.push(neighbor);
                }
                // If neighbor has same color, not bipartite
                else if (color[neighbor] == color[node]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool isBipartite(vector<vector<int>>& adj) {
        int V = adj.size();
        vector<int> color(V, -1);  // -1 means uncolored

        for (int i = 0; i < V; i++) {
            if (color[i] == -1) {
                if (!bfsCheck(i, adj, color))
                    return false;
            }
        }
        return true;
    }

    //////////////////////////////////////////////////////////////////////////////////////

    // Detect cycle in a directed graph using DFS
    // Method 1 Using 2 arrays visited and path visited

    bool dfs(int node, vector<vector<int>>& adj, vector<int>& visited, vector<int>& pathVisited) {
        visited[node] = 1;
        pathVisited[node] = 1;

        for (auto neighbor : adj[node]) {
            if (!visited[neighbor]) {
                if (dfs(neighbor, adj, visited, pathVisited))
                    return true;
            } 
            else if (pathVisited[neighbor]) {
                return true; // back edge found
            }
        }

        pathVisited[node] = 0; // backtrack
        return false;
    }

    bool isCyclic(int V, vector<vector<int>>& adj) {
        vector<int> visited(V, 0), pathVisited(V, 0);

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                if (dfs(i, adj, visited, pathVisited))
                    return true;
            }
        }
        return false;
    }

    ///////////////////////////////
    // Method 2 using single array

    bool dfs(int node, vector<vector<int>>& adj, vector<int>& state) {
        state[node] = 1; // visiting

        for (auto neighbor : adj[node]) {
            if (state[neighbor] == 0) {
                if (dfs(neighbor, adj, state))
                    return true;
            }
            else if (state[neighbor] == 1) {
                return true; // back edge found
            }
        }

        state[node] = 2; // processed
        return false;
    }

    bool isCyclic(int V, vector<vector<int>>& adj) {
        vector<int> state(V, 0); // 0 - unvisited, 1 - visiting, 2 - processed

        for (int i = 0; i < V; i++) {
            if (state[i] == 0) {
                if (dfs(i, adj, state))
                    return true;
            }
        }
        return false;
    }

    //////////////////////////////////////////////////////////////////////////////////////

    // Topo Sort using DFS

    void dfs(int node, vector<int> adj[], vector<int>& vis, stack<int>& st) {
        vis[node] = 1;
        for (auto it : adj[node]) {
            if (!vis[it]) dfs(it, adj, vis, st);
        }
        st.push(node);
    }

    vector<int> topoSort(int V, vector<int> adj[]) {
        vector<int> vis(V, 0);
        stack<int> st;

        for (int i = 0; i < V; i++) {
            if (!vis[i]) dfs(i, adj, vis, st);
        }

        vector<int> topo;
        while (!st.empty()) {
            topo.push_back(st.top());
            st.pop();
        }
        return topo;
    }

    //////////////////////////////////////////////////////////////////////////////////////

    // Kahn's Algo

    vector<int> topoSort(int V, vector<int> adj[]) {
        vector<int> indegree(V, 0);

        // Step 1: Compute indegree of each node
        for (int i = 0; i < V; i++) {
            for (auto it : adj[i]) {
                indegree[it]++;
            }
        }

        // Step 2: Push all nodes with indegree 0 into the queue
        queue<int> q;
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) q.push(i);
        }

        // Step 3: Process queue using BFS
        vector<int> topo;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            topo.push_back(node);

            // Step 4: Reduce indegree of neighbors
            for (auto it : adj[node]) {
                indegree[it]--;
                if (indegree[it] == 0) q.push(it);
            }
        }

        return topo;
    }

    //////////////////////////////////////////////////////////////////////////////////////

    // Detect Cycle in a Directed Graph using Kahn’s Algorithm

    bool isCyclic(int V, vector<int> adj[]) {
        vector<int> indegree(V, 0);

        for (int i = 0; i < V; i++) {
            for (auto it : adj[i]) {
                indegree[it]++;
            }
        }

        queue<int> q;
        for (int i = 0; i < V; i++) {
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

        // If count != V, graph has a cycle
        return count != V;
    }

    //////////////////////////////////////////////////////////////////////////////////////

    // Course Schedule I

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

    //////////////////////////////////////////////////////////////////////////////////////

    // Course Schedule II

    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);
        vector<int> indegree(numCourses, 0);

        // Build adjacency list and indegree array
        for (auto& pre : prerequisites) {
            adj[pre[1]].push_back(pre[0]); // this is important
            indegree[pre[0]]++;
        }

        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) q.push(i);
        }

        vector<int> topo;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            topo.push_back(node);

            for (auto& neighbor : adj[node]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) q.push(neighbor);
            }
        }

        if (topo.size() == numCourses) return topo;
        return {};
    }
    
    //////////////////////////////////////////////////////////////////////////////////////

    // Eventual Safe States Topological Sort

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

    //////////////////////////////////////////////////////////////////////////////////////

    // Alien Dictionary

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

    //////////////////////////////////////////////////////////////////////////////////////

    // Shortest Path in DAG using Topo Sort

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

    //////////////////////////////////////////////////////////////////////////////////////

    // Shortest Path in Undirected Graph with Unit Distance

    vector<int> shortestPath(int n, vector<vector<int>>& edges) {
        // Step 1: Build adjacency list
        vector<vector<int>> adj(n);
        for (auto& e : edges) { // Write loop like this, it is good.
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        // Step 2: Initialize distance array
        const int INF = 1e9;
        vector<int> dist(n, INF);
        dist[0] = 0; // Do not forget to initialize the source

        // Step 3: BFS traversal
        queue<int> q;
        q.push(0);

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int neighbor : adj[node]) { // Update and push
                if (dist[neighbor] > dist[node] + 1) {
                    dist[neighbor] = dist[node] + 1;
                    q.push(neighbor);
                }
            }
        }

        // Step 4: Replace unreachable nodes with -1
        for (int& d : dist) {
            if (d == INF) d = -1;
        }

        return dist;
    }


};

int main() {
    int V, E; 
    cin >> V >> E;

    vector<vector<int>> adj(V);
    for(int i = 0; i < V; i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    return 0;
}
