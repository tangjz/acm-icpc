class Solution {
public:
    int treeOfInfiniteSouls(vector<int>& gem, int p, int target) {
        typedef long long LL;
        static const int maxm = 1 << 9 | 1;
        int maxv = p < 10 ? 10 : 7;
        int n = gem.size(), mx = n * 4 - 1;
        vector<int> sz(n);
        for(int i = 0; i < n; ++i) {
            sz[i] = to_string(gem[i]).size();
            mx += sz[i];
        }
        vector<int> pw(mx + 1), ipw(mx + 1);
        static int bits[maxm] = {}, len[maxm] = {};
        static unordered_map<int, int> f[maxm], g[maxm];
        pw[0] = ipw[0] = 1;
        pw[1] = 10 % p;
        function<int(int)> modInv = [&](int x) {
            return x <= 1 ? x : p - (int)(p / x * (LL)modInv(p % x) % p);
        };
        ipw[1] = modInv(pw[1]);
        for(int i = 2; i < mx; ++i) {
            pw[i] = (LL)pw[1] * pw[i - 1] % p;
            ipw[i] = (LL)ipw[1] * ipw[i - 1] % p;
        }
        for(int i = 0; i < (1 << n); ++i) {
            f[i].clear();
            g[i].clear();
            bits[i] = len[i] = 0;
            int las = -1;
            for(int j = 0; j < n; ++j)
                if((i >> j) & 1) {
                    ++bits[i];
                    len[i] += sz[j];
                    las = j;
                }
            if(!bits[i])
                continue;
            len[i] += 4 * bits[i] - 2;
            // assert(len[i] < mx);
            if(bits[i] == 1) {
                int val = ((pw[sz[las]] + gem[las]) * 10LL + 9) % p;
                ++f[i][val];
                continue;
            }
            if(bits[i] >= maxv)
                continue;
            for(int j = (i - 1) & i; j; j = (j - 1) & i) {
                int u = j, v = i ^ j;
                int pwL = pw[len[u]], pwR = pw[len[v]];
                for(auto &[valL, wayL]: f[u])
                    for(auto &[valR, wayR]: f[v]) {
                        int val = (((pwL + valL) * (LL)pwR + valR) % p * 10 + 9) % p;
                        f[i][val] += wayL * wayR;
                    }
            }
        }
        int ans = 0;
        ++g[(1 << n) - 1][target % p];
        for(int i = (1 << n) - 1; i >= 0; --i) {
            if(bits[i] < maxv) {
                for(auto &[val, way]: g[i]) {
                    auto it = f[i].find(val);
                    if(it != f[i].end())
                        ans += way * (it -> second);
                }
                continue;
            }
            // assert(bits[i] < maxv * 2);
            for(int u = (i - 1) & i; u; u = (u - 1) & i) {
                int v = i ^ u;
                int pwL = pw[len[u]], pwR = pw[len[v]], ipwR = ipw[len[v]];
                if(bits[u] > bits[v]) {
                    for(auto &[val, way]: g[i])
                        for(auto &[valR, wayR]: f[v]) {
                            int valL = (((val - 9LL) * ipw[1] - valR) % p * ipwR - pwL) % p;
                            valL < 0 && (valL += p);
                            g[u][valL] += way * wayR;
                        }
                } else {
                    for(auto &[val, way]: g[i])
                        for(auto &[valL, wayL]: f[u]) {
                            int valR = ((val - 9LL) * ipw[1] - (pwL + valL) * (LL)pwR) % p;
                            valR < 0 && (valR += p);
                            g[v][valR] += way * wayL;
                    }
                }
            }
        }
        return ans;
    }
};
