class Solution {
public:
    vector<int> minOperationsQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        static const int maxn = (int)1e4 + 1, maxd = 15, maxc = 26;
        static int que[maxn], dep[maxn], st[maxd][maxn][maxc + 1], ctr[maxc + 1];
        static vector<pair<int, int> > e[maxn];
        for(auto &it: edges) {
            e[it[0]].push_back({it[1], it[2]});
            e[it[1]].push_back({it[0], it[2]});
        }
        dep[0] = 0;
        st[0][0][0] = -1;
        que[0] = 0;
        for(int i = 0, tot = 1; i < tot; ++i) {
            int u = que[i];
            for(auto &[v, w]: e[u]) {
                if(v == st[0][u][0])
                    continue;
                dep[v] = dep[u] + 1;
                memset(st[0][v], 0, sizeof st[0][0]);
                st[0][v][0] = u;
                ++st[0][v][w];
                que[tot++] = v;
            }
        }
        int mx = 1;
        for( ; (1 << mx) <= dep[que[n - 1]]; ++mx);
        for(int i = 1; i < mx; ++i)
            for(int j = 0; j < n; ++j) {
                int p = st[i - 1][j][0];
                st[i][j][0] = p == -1 ? -1 : st[i - 1][p][0];
                if(st[i][j][0] == -1)
                    continue;
                for(int w = 1; w <= maxc; ++w)
                    st[i][j][w] = st[i - 1][j][w] + st[i - 1][p][w];
            }
        for(int i = 0; i < n; ++i)
            vector<pair<int, int> >().swap(e[i]);
        vector<int> res;
        for(auto &it: queries) {
            int u = it[0], v = it[1];
            memset(ctr, 0, sizeof ctr);
            if(dep[u] < dep[v])
                swap(u, v);
            for(int i = dep[u] - dep[v], j = 0; i > 0; i >>= 1, ++j)
                if(i & 1) {
                    for(int w = 1; w <= maxc; ++w)
                        ctr[w] += st[j][u][w];
                    u = st[j][u][0];
                }
            if(u != v) {
                for(int i = mx - 1; i >= 0; --i)
                    if(st[i][u][0] != st[i][v][0]) {
                        for(int w = 1; w <= maxc; ++w)
                            ctr[w] += st[i][u][w] + st[i][v][w];
                        u = st[i][u][0];
                        v = st[i][v][0];
                    }
                for(int w = 1; w <= maxc; ++w)
                    ctr[w] += st[0][u][w] + st[0][v][w];
            }
            int sum = 0, upp = 0;
            for(int w = 1; w <= maxc; ++w) {
                sum += ctr[w];
                upp = max(upp, ctr[w]);
            }
            res.push_back(sum - upp);
        }
        return res;
    }
};
