class Solution {
public:
    int getFood(vector<vector<char>>& grid) {
        int r = grid.size(), c = grid[0].size(), n = r * c;
        vector<int> dis(n, -1);
        queue<int> que;
        auto upd = [&](int x, int y, int d) {
            if(x < 0 || x >= r || y < 0 || y >= c || grid[x][y] == 'X')
                return;
            int v = x * c + y;
            if(dis[v] == -1) {
                dis[v] = d;
                que.push(v);
            }
        };
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j)
                if(grid[i][j] == '#')
                    upd(i, j, 0);
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            int x = u / c, y = u % c, d = dis[u];
            if(grid[x][y] == '*')
                return d;
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    if(!dx == !dy)
                        continue;
                    upd(x + dx, y + dy, d + 1);
                }
        }
        return -1;
    }
};
