class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        const int INF = 0x3f3f3f3f;
        int n = s1.size(), m = s2.size();
        vector<int> f(m + 1);
        f[0] = 0;
        for(int i = 1; i <= m; ++i)
            f[i] = f[i - 1] + s2[i - 1];
        for(int i = 1; i <= n; ++i)
            for(int j = 0, las = INF, cur; j <= m; ++j) {
                cur = f[j];
                f[j] = min(cur + s1[i - 1], INF);
                if(j) {
                    f[j] = min(f[j], f[j - 1] + s2[j - 1]);
                    if(s1[i - 1] == s2[j - 1])
                        f[j] = min(f[j], las);
                }
                las = cur;
            }
        return f.back();
    }
};
