class Solution {
public:
    int countGoodSubsequences(string s) {
        typedef long long LL;
        static const int mod = (int)1e9 + 7, maxv = (int)1e4 + 1, maxd = 26;
        static vector<int> fct = {1, 1}, ifct = {1, 1}, inv = {0, 1};
        int mx = 0;
        vector<int> ctr(maxd);
        for(char ch: s)
            mx = max(mx, ++ctr[(int)(ch - 'a')]);
        vector<int> ways(mx + 1, 1);
        for(int c: ctr) {
            while(inv.size() <= c) {
                int i = inv.size();
                inv.push_back(mod - (int)(mod / i * (LL)inv[mod % i] % mod));
                fct.push_back((LL)fct.back() * i % mod);
                ifct.push_back((LL)ifct.back() * inv.back() % mod);
            }
            for(int i = 1; i <= c; ++i)
                ways[i] = ((LL)fct[c] * ifct[i] % mod * ifct[c - i] + 1) % mod * ways[i] % mod;
        }
        int ans = 0;
        for(int i = 1; i <= mx; ++i)
            ans = (ans + ways[i] - 1) % mod;
        return ans < 0 ? ans + mod : ans;
    }
};
