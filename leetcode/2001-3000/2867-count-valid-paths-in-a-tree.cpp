class Solution {
public:
    long long countPaths(int n, vector<vector<int>>& edges) {
        typedef long long LL;
        static const int maxv = (int)1e5 + 1;
        static int ptot = 0, d[maxv] = {}, pr[maxv];
        if(!ptot) {
            for(int i = 2; i < maxv; ++i) {
                if(!d[i])
                    pr[ptot++] = d[i] = i;
                for(int j = 0, k; (k = i * pr[j]) < maxv; ++j) {
                    d[k] = pr[j];
                    if(d[i] == pr[j])
                        break;
                }
            }
        }
        vector<int> que = {1}, par(n + 1, -1), f(n + 1), g(n + 1);
        vector<vector<int> > e(n + 1);
        for(auto &it: edges) {
            e[it[0]].push_back(it[1]);
            e[it[1]].push_back(it[0]);
        }
        for(int i = 0; i < n; ++i) {
            int u = que[i];
            for(int v: e[u])
                if(v != par[u]) {
                    par[v] = u;
                    que.push_back(v);
                }
            ++(d[u] == u ? g[u] : f[u]);
        }
        LL ans = 0;
        for(int i = n - 1; i > 0; --i) {
            int u = que[i], p = par[u];
            ans += (LL)f[u] * g[p] + (LL)f[p] * g[u];
            if(d[p] == p) {
                g[p] += f[u];
            } else {
                f[p] += f[u];
                g[p] += g[u];
            }
        }
        return ans;
    }
};
