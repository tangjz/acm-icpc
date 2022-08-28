class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        const int maxd = 4, d[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        int r = (int)grid.size(), c = (int)grid[0].size();
        vector<vector<int> > dist(r, vector<int>(c, INT_MAX)), vis(r, vector<int>(c, 0));
        priority_queue<pair<int, pair<int, int> > > que;
        auto update = [&](int x, int y, int w) -> void {
            if(x < 0 || x >= r || y < 0 || y >= c || dist[x][y] <= w)
                return;
            dist[x][y] = w;
            que.push({-w, {x, y}});
        };
        update(0, 0, 0);
        while(!que.empty()) {
            int x, y;
            tie(x, y) = que.top().second;
            que.pop();
            if(vis[x][y])
                continue;
            vis[x][y] = 1;
            for(int i = 0; i < 4; ++i)
                update(x + d[i][0], y + d[i][1], dist[x][y] + (grid[x][y] - 1 != i));
        }
        return dist[r - 1][c - 1];
    }
};
