class Solution {
public:
    long long minimumCost(string s, string t, vector<string>& qu, vector<string>& qv, vector<int>& qw) {
        typedef long long LL;
        static const int mod = (int)1e9 + 7, seed = 29;
        static unordered_map<int, int> Hash;
        Hash.clear();
        auto getID = [&](int const &key, bool skip = false) {
            if(skip) {
                auto it = Hash.find(key);
                return it == Hash.end() ? -1 : it -> second;
            }
            return Hash.insert({key, (int)Hash.size()}).first -> second;
        };
        auto getHash = [&](string const &s) {
            int hs = 0;
            for(char ch: s) {
                int o = ch - 'a' + 1;
                hs = ((LL)hs * seed + o) % mod;
            }
            return hs;
        };
        int m = qu.size();
        vector<vector<int> > edges;
        vector<int> cand;
        vector<bool> vis;
        auto chk = [&](int len) {
            if(vis.size() <= len)
                vis.resize(len + 1);
            if(!vis[len]) {
                vis[len] = 1;
                cand.push_back(len);
            }
        };
        for(int i = 0; i < m; ++i) {
            int u = getID(getHash(qu[i])), v = getID(getHash(qv[i]));
            edges.push_back({u, v, qw[i]});
            chk(qu[i].size());
            assert(qu[i].size() == qv[i].size());
        }
        sort(cand.begin(), cand.end());
        static const int INF = 0x3f3f3f3f, maxn = 209, maxm = 1009;
        int n = Hash.size();
        static int dis[maxn][maxn];
        for(int i = 0; i < n; ++i) {
            memset(dis[i], 0x3f, n * sizeof(int));
            dis[i][i] = 0;
        }
        for(auto &it: edges) {
            int u = it[0], v = it[1], w = it[2];
            // printf("%d->%d: %d\n", u, v, w);
            dis[u][v] = min(dis[u][v], w);
        }
        for(int k = 0; k < n; ++k)
            for(int i = 0; i < n; ++i) if(dis[i][k] < INF)
                for(int j = 0; j < n; ++j) if(dis[k][j] < INF)
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
        static const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
        m = s.size();
        static int hs[maxm], ht[maxm], pw[maxm];
        hs[0] = 0;
        pw[0] = 1;
        for(int i = 0; i < m; ++i) {
            int o = s[i] - 'a' + 1, p = t[i] - 'a' + 1;
            hs[i + 1] = ((LL)hs[i] * seed + o) % mod;
            ht[i + 1] = ((LL)ht[i] * seed + p) % mod;
            pw[i + 1] = (LL)pw[i] * seed % mod;
        }
        auto query = [&](int hs[], int L, int R) {
            int hh = (hs[R + 1] - (LL)hs[L] * pw[R - L + 1]) % mod;
            return hh < 0 ? hh + mod : hh;
        };
        static LL dp[maxm];
        memset(dp + 1, 0x3f, m * sizeof(LL));
        dp[0] = 0;
        for(int i = 0; i < m; ++i) {
            if(dp[i] == INFLL)
                continue;
            if(s[i] == t[i])
                dp[i + 1] = min(dp[i + 1], dp[i]);
            for(int len: cand) {
                if(len > m - i)
                    break;
                int ss = query(hs, i, i + len - 1), tt = query(ht, i, i + len - 1);
                int u = getID(ss, true), v = getID(tt, true);
                // printf("[%d, %d]: %d %d\n", i, j, u, v);
                if(u == -1 || v == -1 || dis[u][v] == INF)
                    continue;
                dp[i + len] = min(dp[i + len], dp[i] + dis[u][v]);
            }
        }
        return dp[m] < INFLL ? dp[m] : -1;
    }
};
