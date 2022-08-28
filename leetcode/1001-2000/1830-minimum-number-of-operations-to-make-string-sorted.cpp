class Solution {
public:
    int makeStringSorted(string s) {
        typedef long long LL;
        const int mod = (int)1e9 + 7, maxd = 26;
        int n = (int)s.size();
        vector<int> fct(n + 1), ivs(n + 1);
        ivs[1] = 1;
        for(int i = 2; i <= n; ++i)
            ivs[i] = mod - (int)(mod / i * (LL)ivs[mod % i] % mod);
        fct[0] = ivs[0] = 1;
        for(int i = 1; i <= n; ++i) {
            fct[i] = (LL)fct[i - 1] * i % mod;
            ivs[i] = (LL)ivs[i - 1] * ivs[i] % mod;
        }
        vector<int> ctr(maxd);
        for(char ch: s)
            ++ctr[(int)(ch - 'a')];
        int ans = 0, pos = 0;
        for(char ch: s) {
            int o = ch - 'a';
            int tmp = 0;
            for(int i = 0; i < o; ++i)
                tmp += ctr[i];
            tmp = (LL)tmp * fct[n - (++pos)] % mod;
            for(int i = 0; i < maxd; ++i)
                tmp = (LL)tmp * ivs[ctr[i]] % mod;
            ans = (ans + tmp) % mod;
            --ctr[o];
        }
        return ans;
    }
};
