class Solution {
    bool match(string const &s, string const &t, vector<int> const &f) {
        int n = s.size(), m = t.size();
        for(int i = 0, j = 0; i < n; ++i) {
            for( ; j && s[i] != t[j]; j = f[j]);
            if(s[i] == t[j])
                ++j;
            if(j == m)
                return 1;
        }
        return 0;
    }
public:
    int repeatedStringMatch(string a, string b) {
        int n = a.size(), m = b.size();
        for(int i = n; i < m; ++i)
            if(b[i] != b[i - n])
                return -1;
        vector<int> f(m + 1);
        for(int i = 1, j = 0; i < m; ++i) {
            for( ; j && b[i] != b[j]; j = f[j]);
            f[i + 1] = b[i] == b[j] ? (++j) : 0;
        }
        int q = (m - 1) / n + 1;
        string c = "";
        for(int i = 0; i < q; ++i)
            c += a;
        if(match(c, b, f))
            return q;
        c += a;
        return match(c, b, f) ? q + 1 : -1;
    }
};
