class Solution {
public:
    int maxProduct(string s) {
        int ans = 0, n = s.length(), m = 1 << n;
        vector<int> f(m), g(m);
        for(int msk1 = 1; msk1 < (1 << n); ++msk1) {
            string fir, firRev;
            for(int i = 0; i < n; ++i)
                if((msk1 >> i) & 1) {
                    fir += s[i];
                    firRev = s[i] + firRev;
                }
            if(fir == firRev)
                f[msk1] = g[msk1] = fir.size();
        }
        for(int i = 1; i < m; i <<= 1)
            for(int j = 0; j < m; ++j)
                if(j & i)
                    g[j] = max(g[j], g[j ^ i]);
        for(int i = 0; i < m; ++i)
            ans = max(ans, f[i] * g[m - 1 - i]);
        return ans;
    }
};
