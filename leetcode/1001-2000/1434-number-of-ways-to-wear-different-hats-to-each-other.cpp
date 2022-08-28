typedef long long LL;
class Solution {
    static const int maxd = 41, mod = (int)1e9 + 7;
    int n;
    vector<int> lens, cnts, masks;
    int dfs(int dep, int tot) {
        if(dep == n) {
            int ans = 1;
            for(int i = 0; i < tot; ++i) {
                for(int j = 1; j < cnts[i]; ++j)
                    ans = (LL)ans * (mod - j) % mod;
                ans = (LL)ans * lens[masks[i]] % mod;
            }
            return ans;
        }
        int ret = 0;
        for(int i = 0; i <= tot; ++i) {
            ++cnts[i];
            masks[i] ^= 1 << dep;
            (ret += dfs(dep + 1, tot + (i == tot))) >= mod && (ret -= mod);
            --cnts[i];
            masks[i] ^= 1 << dep;
        }
        return ret;
    }
public:
    int numberWays(vector<vector<int>>& hats) {
        vector<int>().swap(lens);
        n = (int)hats.size();
        for(int i = 0; i < (1 << n); ++i) {
            int bits = 0;
            static int ctr[maxd];
            for(int j = 1; j < maxd; ++j)
                ctr[j] = 0;
            for(int j = 0; j < n; ++j) {
                if(!((i >> j) & 1))
                    continue;
                ++bits;
                for(int k : hats[j])
                    ++ctr[k];
            }
            int cnt = 0;
            for(int j = 1; j < maxd; ++j)
                cnt += ctr[j] == bits;
            lens.push_back(cnt);
        }
        vector<int>().swap(cnts);
        vector<int>().swap(masks);
        for(int i = 0; i < n; ++i) {
            cnts.push_back(0);
            masks.push_back(0);
        }
        return dfs(0, 0);
    }
};
