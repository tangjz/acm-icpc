class Solution {
public:
    int cherryPickup(vector<vector<int>>& a) {
        int r = (int)a.size(), c = (int)a[0].size();
        vector<vector<int> > f(c, vector<int>(c, INT_MIN));
        f[0][c - 1] = a[0][0] + a[0][c - 1];
        for(int i = 1; i < r; ++i) {
            vector<vector<int> > g(c, vector<int>(c, INT_MIN));
            for(int j = 0; j < c; ++j)
                for(int k = 0; k < c; ++k) {
                    if(f[j][k] < 0)
                        continue;
                    for(int dx = -1; dx <= 1; ++dx) {
                        int x = j + dx;
                        if(x < 0 || x >= c)
                            continue;
                        for(int dy = -1; dy <= 1; ++dy) {
                            int y = k + dy;
                            if(y < 0 || y >= c)
                                continue;
                            g[x][y] = max(g[x][y], f[j][k] + a[i][x] + (x == y ? 0 : a[i][y]));
                        }
                    }
                }
            f = move(g);
        }
        int ans = INT_MIN;
        for(int i = 0; i < c; ++i)
            for(int j = 0; j < c; ++j)
                ans = max(ans, f[i][j]);
        return ans;
    }
};
