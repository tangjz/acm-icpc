class Solution {
public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        int r = maze.size(), c = maze[0].size(), n = r * c;
        int s = start[0] * c + start[1];
        int t = destination[0] * c + destination[1];
        vector<vector<int> > e(n);
        for(int i = 0; i < r; ++i) {
            for(int j = 0, idx = i * c, k = j; j < c; ++j, ++idx) {
                if(maze[i][j]) {
                    k = j + 1;
                    continue;
                }
                if(j > k) {
                    int dt = j - k;
                    e[idx - dt].push_back(idx);
                }
            }
            for(int j = c - 1, idx = (i + 1) * c - 1, k = j; j >= 0; --j, --idx) {
                if(maze[i][j]) {
                    k = j - 1;
                    continue;
                }
                if(j < k) {
                    int dt = k - j;
                    e[idx + dt].push_back(idx);
                }
            }
        }
        for(int j = 0; j < c; ++j) {
            for(int i = 0, idx = j, k = i; i < r; ++i, idx += c) {
                if(maze[i][j]) {
                    k = i + 1;
                    continue;
                }
                if(i > k) {
                    int dt = i - k;
                    e[idx - dt * c].push_back(idx);
                }
            }
            for(int i = r - 1, idx = i * c + j, k = i; i >= 0; --i, idx -= c) {
                if(maze[i][j]) {
                    k = i - 1;
                    continue;
                }
                if(i < k) {
                    int dt = k - i;
                    e[idx + dt * c].push_back(idx);
                }
            }
        }
        vector<bool> vis(n);
        queue<int> que;
        vis[t] = 1;
        que.push(t);
        while(!que.empty()) {
            int v = que.front();
            que.pop();
            for(int u: e[v])
                if(!vis[u]) {
                    vis[u] = 1;
                    que.push(u);
                }
        }
        return vis[s];
    }
};
