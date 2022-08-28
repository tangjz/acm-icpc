class Solution {
public:
    int trapRainWater(vector<vector<int>>& mat) {
        int r = mat.size(), c = mat[0].size(), n = r * c + 1;
        vector<int> dsu(n, -1);
        function<int(int)> dsuFind = [&](int u) {
            return dsu[u] < 0 ? u : (dsu[u] = dsuFind(dsu[u]));
        };
        auto dsuMerge = [&](int u, int v) {
            // printf("merge %d %d\n", u, v);
            u = dsuFind(u);
            v = dsuFind(v);
            if(u == v)
                return;
            if(dsu[u] < dsu[v])
                swap(u, v);
            dsu[v] += dsu[u];
            dsu[u] = v;
        };
        map<int, vector<int> > mp;
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j)
                mp[mat[i][j]].push_back(i * c + j);
        int ans = 0, cnt = 1;
        for(auto jt = mp.begin(), it = jt++; jt != mp.end(); it = jt++) {
            for(int u: it -> second) {
                int x = u / c, y = u % c;
                ++cnt;
                for(int dx = -1; dx <= 1; ++dx)
                    for(int dy = -1; dy <= 1; ++dy) {
                        if(!dx == !dy)
                            continue;
                        int v, xx = x + dx, yy = y + dy;
                        if(xx < 0 || xx >= r || yy < 0 || yy >= c) {
                            v = n - 1;
                        } else {
                            if(mat[xx][yy] > it -> first)
                                continue;
                            v = u + dx * c + dy;
                        }
                        dsuMerge(u, v);
                    }
            }
            // printf("height [%d, %d): cnt %d blk %d\n", it -> first, jt -> first, cnt, -dsu[dsuFind(n - 1)]);
            ans += (jt -> first - it -> first) * (cnt + dsu[dsuFind(n - 1)]);
        }
        return ans;
    }
};
