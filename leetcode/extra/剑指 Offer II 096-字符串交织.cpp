class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n = s1.size(), m = s2.size();
        if(s3.size() != n + m)
            return 0;
        vector<bool> f(m + 1);
        f[0] = 1;
        for(int i = 1; i <= m; ++i)
            f[i] = f[i - 1] && s2[i - 1] == s3[i - 1];
        for(int i = 1; i <= n; ++i)
            for(int j = 0; j <= m; ++j) {
                bool old = f[j];
                f[j] = (old && s1[i - 1] == s3[i + j - 1]) || (j > 0 && f[j - 1] && s2[j - 1] ==  s3[i + j - 1]);
            }
        return f.back();
    }
};
