class Solution {
public:
    int countSubstrings(string s, string t) {
        int ans = 0, n = s.size(), m = t.size();
        vector<vector<int> > pre(n, vector<int>(m)), suf(n, vector<int>(m));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                pre[i][j] = s[i] == t[j] ? (i > 0 && j > 0 ? pre[i - 1][j - 1] + 1 : 1) : 0;
        for(int i = n - 1; i >= 0; --i)
            for(int j = m - 1; j >= 0; --j)
                suf[i][j] = s[i] == t[j] ? (i + 1 < n && j + 1 < m ? suf[i + 1][j + 1] + 1 : 1) : 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                if(s[i] != t[j])
                    ans += (i > 0 && j > 0 ? pre[i - 1][j - 1] + 1 : 1) * (i + 1 < n && j + 1 < m ? suf[i + 1][j + 1] + 1 : 1);
        return ans;
    }
};
