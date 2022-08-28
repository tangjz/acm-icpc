class Solution {
public:
    int largestArea(vector<string>& grid) {
        int ans = 0, r = grid.size(), c = grid[0].size();
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j) {
                if(grid[i][j] == '0' || !grid[i][j])
                    continue;
                bool ban = 0;
                int sz = 0;
                queue<pair<int, int> > que;
                char ch = grid[i][j];
                grid[i][j] = '\0';
                que.push({i, j});
                while(!que.empty()) {
                    int x, y;
                    tie(x, y) = que.front();
                    // printf("%d %d\n", x, y);
                    que.pop();
                    ++sz;
                    for(int dx = -1; dx <= 1; ++dx)
                        for(int dy = -1; dy <= 1; ++dy) {
                            if(!dx == !dy)
                                continue;
                            int xx = x + dx, yy = y + dy;
                            if(xx < 0 || xx >= r || yy < 0 || yy >= c || grid[xx][yy] == '0') {
                                ban = 1;
                                continue;
                            }
                            if(grid[xx][yy] != ch)
                                continue;
                            grid[xx][yy] = '\0';
                            que.push({xx, yy});
                        }
                }
                // printf("sz %d ban %d\n", sz, ban);
                if(!ban)
                    ans = max(ans, sz);
            }
        return ans;
    }
};
