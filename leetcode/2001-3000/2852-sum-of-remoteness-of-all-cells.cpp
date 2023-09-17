class Solution {
public:
    long long sumRemoteness(vector<vector<int>>& grid) {
        typedef long long LL;
        int r = grid.size(), c = grid[0].size(), cnt = 0;
        LL ans = 0, sum = 0;
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j) {
                if(grid[i][j] == -1)
                    continue;
                int cnt2 = 0;
                LL sum2 = 0;
                static queue<pair<int, int> > que;
                for( ; !que.empty(); que.pop());
                auto upd = [&](int x, int y) {
                    if(x < 0 || x >= r || y < 0 || y >= c || grid[x][y] == -1)
                        return;
                    que.push({x, y});
                    ++cnt2;
                    sum2 += grid[x][y];
                    grid[x][y] = -1;
                };
                upd(i, j);
                while(!que.empty()) {
                    auto [x, y] = que.front();
                    que.pop();
                    for(int dx = -1; dx <= 1; ++dx)
                        for(int dy = -1; dy <= 1; ++dy)
                            if(!dx != !dy)
                                upd(x + dx, y + dy);
                }
                cnt += cnt2;
                sum += sum2;
                ans -= cnt2 * sum2;
            }
        ans += cnt * sum;
        return ans;
    }
};
