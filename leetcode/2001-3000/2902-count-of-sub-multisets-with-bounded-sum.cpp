class Solution {
public:
    int countSubMultisets(vector<int>& nums, int l, int r) {
        typedef long long LL;
        static const int maxv = (int)2e4 + 1, mod = (int)1e9 + 7;
        static int f[maxv], g[maxv];
        unordered_map<int, int> ctr;
        for(int x: nums)
            ++ctr[x];
        memset(f + 1, 0, r * sizeof(int));
        f[0] = 1;
        for(auto &it: ctr) {
            int u = it.first, v = it.first * it.second;
            if(!u) {
                for(int i = 0; i <= r; ++i)
                    f[i] = f[i] * (it.second + 1LL) % mod;
                continue;
            }
            memset(g, 0, u * sizeof(int));
            for(int i = r, j = i % u; i >= 0; --i, (--j) < 0 && (j += u)) {
                (g[j] += f[i]) >= mod && (g[j] -= mod);
                if(i + v <= r) {
                    int tp = g[j];
                    (g[j] -= f[i + v]) < 0 && (g[j] += mod);
                    f[i + v] = tp;
                }
            }
            for(int i = min(r, v - 1), j = i % u; i >= 0; --i, (--j) < 0 && (j += u)) {
                int tp = g[j];
                (g[j] -= f[i]) < 0 && (g[j] += mod);
                f[i] = tp;
            }
        }
        int ans = 0;
        for(int i = l; i <= r; ++i)
            (ans += f[i]) >= mod && (ans -= mod);
        return ans;
    }
};
