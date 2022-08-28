class Solution {
public:
    bool isMatch(string s, string p) {
        int n = (int)s.size(), m = (int)p.size();
        vector<bool> f(m + 1);
        f[0] = true;
        for(int i = 0; i < n; ++i) {
            vector<bool> g(m + 1);
            for(int j = 0; j < m; ++j) {
                if(!f[j])
                    continue;
                if(p[j] == '?' || s[i] == p[j])
                    g[j + 1] = true;
                if(p[j] == '*')
                    f[j + 1] = g[j] = true;
            }
            f = move(g);
        }
        for(int j = 0; j < m; ++j)
            if(p[j] == '*' && f[j])
                f[j + 1] = true;
        return f[m];
    }
};
