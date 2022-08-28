class Solution {
public:
    int longestCommonSubpath(int n, vector<vector<int>>& paths) {
        typedef long long LL;
        const int mod1 = (int)1e9 + 7, mod2 = (int)1e9 + 403;
        const int seed1 = 37, seed2 = 29;
        int m = paths.size(), mx = 0, tot = 0;
        vector<vector<pair<int, int> > > hs(m);
        sort(paths.begin(), paths.end(), [&](auto const &u, auto const &v) {
            return u.size() < v.size();
        });
        for(int i = 0; i < m; ++i) {
            int sz = paths[i].size();
            tot += sz;
            mx = max(mx, sz);
            hs[i].reserve(sz + 1);
            hs[i].push_back({0, 0});
            for(int c: paths[i]) {
                int x, y;
                tie(x, y) = hs[i].back();
                x = ((LL)x * seed1 + c) % mod1;
                y = ((LL)y * seed2 + c) % mod2;
                hs[i].push_back({x, y});
            }
        }
        vector<pair<int, int> > pw;
        pw.reserve(mx + 1);
        pw.push_back({1, 1});
        for(int i = 1; i <= mx; ++i) {
            int x, y;
            tie(x, y) = pw.back();
            x = (LL)x * seed1 % mod1;
            y = (LL)y * seed2 % mod2;
            pw.push_back({x, y});
        }
        int L = 0, R = mx;
        while(L < R) {
            int M = (L + R + 1) >> 1;
            unordered_set<LL> f;
            int xP, yP;
            tie(xP, yP) = pw[M];
            for(int i = 0; i < m; ++i) {
                int sz = paths[i].size();
                unordered_set<LL> g;
                g.reserve(paths[0].size());
                for(int j = 0; j <= sz - M; ++j) {
                    int xL, yL, xR, yR;
                    tie(xL, yL) = hs[i][j];
                    tie(xR, yR) = hs[i][j + M];
                    int x = (xR - (LL)xL * xP) % mod1;
                    x < 0 && (x += mod1);
                    int y = (yR - (LL)yL * yP) % mod2;
                    y < 0 && (y += mod2);
                    LL msk = (LL)x << 32 | y;
                    if(i > 0 && !f.count(msk)) {
                        continue;
                    }
                    g.insert(msk);
                    if(i == m - 1)
                        break;
                }
                f = move(g);
            }
            if(!f.empty()) {
                L = M;
            } else {
                R = M - 1;
            }
        }
        return L;
    }
};
