class Solution {
public:
    int findMaxFish(vector<vector<int>>& grid) {
        int r = grid.size(), c = grid[0].size(), ans = 0;
        queue<int> que;
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j) {
                if(!grid[i][j])
                    continue;
                int cnt = 0;
                auto upd = [&](int x, int y) {
                    if(x < 0 || x >= r || y < 0 || y >= c || !grid[x][y])
                        return;
                    cnt += grid[x][y];
                    grid[x][y] = 0;
                    que.push(x * c + y);
                };
                upd(i, j);
                while(!que.empty()) {
                    int u = que.front(), ux = u / c, uy = u % c;
                    que.pop();
                    for(int dx = -1; dx <= 1; ++dx)
                        for(int dy = -1; dy <= 1; ++dy) {
                            if(!dx == !dy)
                                continue;
                            upd(ux + dx, uy + dy);
                        }
                }
                ans = max(ans, cnt);
            }
        return ans;
    }
};
