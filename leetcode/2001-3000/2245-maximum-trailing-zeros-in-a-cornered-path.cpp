class Solution {
    static const int maxd = 4;
    static constexpr int dx[maxd] = {-1, 0, 1, 0}, dy[maxd] = {0, 1, 0, -1};

    pair<int, int> zero = {};

    pair<int, int> &F(int d, int x, int y, vector<vector<pair<int, int> > > &adt, vector<vector<vector<pair<int, int> > > > &f) {
        if(x < 0 || x >= f[d].size() || y < 0 || y >= f[d][x].size())
            return zero;
        pair<int, int> &ret = f[d][x][y];
        if(ret.first == -1) {
            pair<int, int> &nxt = F(d, x + dx[d], y + dy[d], adt, f), &com = adt[x][y];
            ret = {nxt.first + com.first, nxt.second + com.second};
            // printf("%d %d %d: %d %d\n", d, x, y, ret.first, ret.second);
        }
        return ret;
    }

public:
    int maxTrailingZeros(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size(), ans = 0;
        vector<vector<pair<int, int> > > adt(n, vector<pair<int, int> >(m));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                int x = grid[i][j];
                for( ; !(x & 1); ++adt[i][j].first, x >>= 1);
                for( ; x % 5 == 0; ++adt[i][j].second, x /= 5);
            }
        vector<vector<vector<pair<int, int> > > > f(maxd, vector<vector<pair<int, int> > >(n, vector<pair<int, int> >(m, {-1, -1})));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                auto &com = adt[i][j];
                for(int p = 0; p < maxd; ++p) {
                    auto &it = F(p, i, j, adt, f);
                    ans = max(ans, min(it.first, it.second));
                    for(int q = p + 1; q < maxd; ++q) {
                        if(p + 2 == q)
                            continue;
                        auto &jt = F(q, i, j, adt, f);
                        ans = max(ans, min(it.first + jt.first - com.first, it.second + jt.second - com.second));
                    }
                }
            }
        return ans;
    }
};
