class Solution {
public:
    int minimumMoves(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<vector<int> > > dis(2, vector<vector<int> >(n, vector<int>(n, -1)));
        queue<vector<int> > que;
        auto upd = [&](bool t, int x, int y, int d) {
            if(x < 0 || x >= n || y < 0 || y >= n || grid[x][y] || dis[t][x][y] != -1)
                return;
            int xx = x + !!t, yy = y + !t;
            if(xx >= n || yy >= n || grid[xx][yy])
                return;
            dis[t][x][y] = d;
            que.push({(int)t, x, y});
        };
        upd(0, 0, 0, 0);
        while(!que.empty()) {
            auto &it = que.front();
            int t = it[0], x = it[1], y = it[2], d = dis[t][x][y];
            // printf("(%d %d) (%d %d): %d\n", x, y, x + !!t, y + !t, d);
            que.pop();
            upd(t, x + 1, y, d + 1);
            upd(t, x, y + 1, d + 1);
            if(!t) {
                if(x + 1 < n && dis[t][x + 1][y] != -1)
                    upd(!t, x, y, d + 1);
            } else {
                if(y + 1 < n && dis[t][x][y + 1] != -1)
                    upd(!t, x, y, d + 1);
            }
        }
        return dis[0][n - 1][n - 2];
    }
};
