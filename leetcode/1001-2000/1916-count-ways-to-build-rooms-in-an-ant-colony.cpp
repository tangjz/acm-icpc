class Solution {
public:
    int waysToBuildRooms(vector<int>& par) {
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        int n = par.size(), ans = 1;
        vector<int> inv(n + 1), sz(n), ord;
        vector<vector<int> > e(n);
        inv[1] = 1;
        for(int i = 2; i <= n; ++i) {
            ans = (LL)ans * i % mod;
            inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
            e[par[i - 1]].push_back(i - 1);
        }
        ord.push_back(0);
        for(int i = 0; i < n; ++i) {
            int u = ord[i];
            for(int v: e[u])
                ord.push_back(v);
        }
        for(int i = n - 1; i >= 0; --i) {
            int u = ord[i];
            ans = (LL)ans * inv[++sz[u]] % mod;
            if(par[u] >= 0)
                sz[par[u]] += sz[u];
        }
        return ans;
    }
};
