class Solution {
    typedef long long LL;
    static const int mod = (int)1e9 + 7;
public:
    vector<int> bonus(int n, vector<vector<int>>& leadership, vector<vector<int>>& operations) {
        int tot = 0;
        vector<int> s0(n + 1), s1(n + 1), in(n), out(n);
        vector<vector<int> > e(n);
        for(auto &it: leadership)
            e[--it[0]].push_back(--it[1]);
        function<void(int)> dfs = [&](int u) {
            in[u] = ++tot;
            for(int v: e[u])
                dfs(v);
            out[u] = tot;
        };
        dfs(0);
        auto bitUpd = [&](int x, int v) {
            int v0 = v, v1 = (LL)v0 * x % mod;
            for( ; x <= n; x += x & -x) {
                (s0[x] += v0) >= mod && (s0[x] -= mod);
                (s1[x] += v1) >= mod && (s1[x] -= mod);
            }
        };
        auto bitQue = [&](int x) {
            int v0 = 0, v1 = 0;
            for(int i = x; i > 0; i -= i & -i) {
                (v0 += s0[i]) >= mod && (v0 -= mod);
                (v1 += s1[i]) >= mod && (v1 -= mod);
            }
            v0 = ((x + 1LL) * v0 - v1) % mod;
            return v0 < 0 ? v0 + mod : v0;
        };
        vector<int> ret;
        for(auto &it: operations) {
            --it[1];
            if(it[0] == 1) {
                bitUpd(in[it[1]], it[2]);
                bitUpd(in[it[1]] + 1, mod - it[2]);
            } else if(it[0] == 2) {
                bitUpd(in[it[1]], it[2]);
                bitUpd(out[it[1]] + 1, mod - it[2]);
            } else {
                int ans = bitQue(out[it[1]]) - bitQue(in[it[1]] - 1);
                ret.push_back(ans < 0 ? ans + mod : ans);
            }
        }
        return ret;
    }
};
