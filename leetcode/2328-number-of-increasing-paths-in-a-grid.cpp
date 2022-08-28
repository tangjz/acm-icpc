class Solution {
public:
    int countPaths(vector<vector<int>>& grid) {
        const int mod = (int)1e9 + 7;
        int r = grid.size(), c = grid[0].size();
        vector<vector<int> > dp(r, vector<int>(c, -1));
        function<int(int, int)> calc = [&](int x, int y) {
            int &ret = dp[x][y];
            if(ret == -1) {
                ret = 1;
                for(int dx = -1; dx <= 1; ++dx)
                    for(int dy = -1; dy <= 1; ++dy) {
                        if(!dx == !dy)
                            continue;
                        int xx = x + dx, yy = y + dy;
                        if(xx < 0 || xx >= r || yy < 0 || yy >= c || grid[xx][yy] >= grid[x][y])
                            continue;
                        ret = (ret + calc(xx, yy)) % mod;
                    }
            }
            return ret;
        };
        int ans = 0;
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j)
                ans = (ans + calc(i, j)) % mod;
        return ans;
    }
};
