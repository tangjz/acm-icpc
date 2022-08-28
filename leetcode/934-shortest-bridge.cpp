class Solution {
public:
    int shortestBridge(vector<vector<int>>& grid) {
        int r = grid.size(), c = grid[0].size();
        queue<pair<int, int> > que;
        for(int i = 0; i < r && que.empty(); ++i)
            for(int j = 0; j < c && que.empty(); ++j) {
                if(grid[i][j] != 1)
                    continue;
                queue<pair<int, int> > que2;
                grid[i][j] = -1;
                que2.push({i, j});
                while(!que2.empty()) {
                    int ux, uy;
                    tie(ux, uy) = que2.front();
                    que.push({ux, uy});
                    // printf("que2 %d %d\n", ux, uy);
                    que2.pop();
                    for(int dx = -1; dx <= 1; ++dx)
                        for(int dy = -1; dy <= 1; ++dy) {
                            if(!dx == !dy)
                                continue;
                            int vx = ux + dx, vy = uy + dy;
                            if(vx < 0 || vx >= r || vy < 0 || vy >= c || grid[vx][vy] != 1)
                                continue;
                            grid[vx][vy] = -1;
                            que2.push({vx, vy});
                        }
                }
            }
        while(!que.empty()) {
            int ux, uy;
            tie(ux, uy) = que.front();
            que.pop();
            int nxt = grid[ux][uy] - 1;
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    if(!dx == !dy)
                        continue;
                    int vx = ux + dx, vy = uy + dy;
                    if(vx < 0 || vx >= r || vy < 0 || vy >= c || grid[vx][vy] < 0)
                        continue;
                    // printf("que1 %d %d %d\n", vx, vy, nxt);
                    if(grid[vx][vy] == 1)
                        return -nxt - 2;
                    grid[vx][vy] = nxt;
                    que.push({vx, vy});
                }
        }
        return -1;
    }
};
