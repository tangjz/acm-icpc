class Solution {
public:
    int distinctSubseqII(string s) {
        const int maxd = 26, mod = (int)1e9 + 7;
        vector<int> f(maxd + 1);
        f[maxd] = 1;
        for(char ch: s) {
            int o = ch - 'a';
            swap(f[o], f[maxd]);
            f[maxd] = (f[o] * 2 - f[maxd]) % mod;
            f[maxd] < 0 && (f[maxd] += mod);
        }
        int ans = f[maxd] - 1;
        ans < 0 && (ans += mod);
        return ans;
    }
};
