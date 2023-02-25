class Solution {
public:
    int minimumScore(string s, string t) {
        int n = s.size(), m = t.size();
        int ans = m;
        vector<int> pre(m), suf(m);
        for(int i = 0, j = 0; i < m; ++i) {
            for( ; j < n && s[j] != t[i]; ++j);
            pre[i] = j;
            if(j < n)
                ans = min(ans, m - 1 - i);
            if(j < n && s[j] == t[i])
                ++j;
        }
        for(int i = m - 1, j = n - 1; i >= 0; --i) {
            for( ; j >= 0 && s[j] != t[i]; --j);
            suf[i] = j;
            if(j >= 0)
                ans = min(ans, i);
            if(j >= 0 && s[j] == t[i])
                --j;
        }
        for(int i = 1, j = 0; i < m && pre[i - 1] < n; ++i) {
            for( ; j + 1 < m && suf[j + 1] <= pre[i - 1]; ++j);
            if(j + 1 < m)
                ans = min(ans, max(j - i + 1, 0));
        }
        return ans;
    }
};
