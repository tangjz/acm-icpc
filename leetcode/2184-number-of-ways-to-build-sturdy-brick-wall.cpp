class Solution {
public:
    int buildWall(int n, int m, vector<int>& seq) {
        int mx = 1 << m;
        vector<int> vis(mx), msk;
        for(int x: seq)
            if(x <= m)
                vis[1 << (x - 1)] = 1;
        for(int i = 1; i < mx; ++i) {
            if(!vis[i])
                continue;
            int j = m - 1;
            for( ; !((i >> j) & 1); --j);
            if(j == m - 1) {
                msk.push_back(i ^ (1 << j));
                continue;
            }
            for(int x: seq)
                if(j + x < m)
                    vis[i | 1 << (j + x)] = 1;
        }
        m = msk.size();
        vector<vector<int> > e(m); // sum(len) <= 3 ** m
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < m; ++j)
                if(!(msk[i] & msk[j]))
                    e[i].push_back(j);
        const int mod = (int)1e9 + 7;
        vector<int> f(m, 1), g(m);
        for(int i = 1; i < n; ++i) {
            g.assign(m, 0);
            for(int j = 0; j < m; ++j) {
                if(!f[j])
                    continue;
                for(int k: e[j])
                    (g[k] += f[j]) >= mod && (g[k] -= mod);
            }
            f.swap(g);
        }
        int ans = 0;
        for(int x: f)
            (ans += x) >= mod && (ans -= mod);
        return ans;
    }
};
