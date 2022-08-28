class Solution {
public:
    int numberOfGoodSubsets(vector<int>& nums) {
        const int maxv = 31;
        int tot = 0;
        int msk[maxv] = {}, vis[maxv] = {};
        for(int i = 2; i < maxv; ++i) {
            if(vis[i])
                continue;
            for(int j = i; j < maxv; j += i) {
                msk[j] = msk[j] != -1 && j / i % i > 0 ? msk[j] | (1 << tot) : -1;
                vis[j] = 1;
            }
            ++tot;
        }
        // printf("tot: %d\n", tot);
        // printf("msk %d: %d\n", i, msk[i]);
        unordered_map<int, int> ctr;
        for(int x: nums)
            ++ctr[x];
        const int mod = (int)1e9 + 7;
        vector<int> f(1 << tot);
        f[0] = 1;
        for(int i = ctr[1]; i > 0; --i)
            f[0] = 2LL * f[0] % mod;
        ctr.erase(1);
        for(auto &it: ctr) {
            int s = msk[it.first];
            if(s == -1)
                continue;
            vector<int> g(f.begin(), f.end());
            for(int i = 0; i < (1 << tot); ++i) {
                if(s & i)
                    continue;
                g[s | i] = (g[s | i] + 1LL * f[i] * it.second) % mod;
            }
            f = move(g);
        }
        int ans = 0;
        for(int i = 1; i < (1 << tot); ++i)
            ans = (ans + f[i]) % mod;
        return ans;
    }
};
