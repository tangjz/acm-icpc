class Solution {
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        const int INF = INT_MAX;
        int n = maze.size(), m = maze[0].size();
        vector<int> dis(n * m, INF);
        queue<int> que;
        auto check = [&](int u, int d) {
            if(dis[u] <= d)
                return;
            dis[u] = d;
            que.push(u);
        };
        maze[entrance[0]][entrance[1]] = '+';
        for(int i = 0; i < n; ++i) {
            if(maze[i][0] == '.')
                check(i * m + 0, 0);
            if(maze[i][m - 1] == '.')
                check(i * m + m - 1, 0);
        }
        for(int i = 0; i < m; ++i) {
            if(maze[0][i] == '.')
                check(0 * m + i, 0);
            if(maze[n - 1][i] == '.')
                check((n - 1) * m + i, 0);
        }
        maze[entrance[0]][entrance[1]] = '.';
        while(!que.empty()) {
            int u = que.front(), ux = u / m, uy = u % m;
            que.pop();
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    if(!!dx == !!dy)
                        continue;
                    int vx = ux + dx, vy = uy + dy, v = vx * m + vy;
                    if(vx < 0 || vx >= n || vy < 0 || vy >= m || maze[vx][vy] != '.')
                        continue;
                    check(v, dis[u] + 1);
                }
        }
        int ans = dis[entrance[0] * m + entrance[1]];
        return ans < INF ? ans : -1;
    }
};
