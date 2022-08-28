class Solution {
public:
    int countPalindromicSubsequence(string s) {
        int n = s.size();
        vector<int> pre(n), suf(n);
        for(int i = 0; i < n; ++i) {
            int o = s[i] - 'a';
            pre[i] = (i > 0 ? pre[i - 1] : 0) | 1 << o;
        }
        for(int i = n - 1; i >= 0; --i) {
            int o = s[i] - 'a';
            suf[i] = (i + 1 < n ? suf[i + 1] : 0) | 1 << o;
        }
        const int maxd = 26;
        vector<int> msk(maxd);
        for(int i = 0; i < n; ++i) {
            int o = s[i] - 'a';
            int tmp = (i > 0 ? pre[i - 1] : 0) & (i + 1 < n ? suf[i + 1] : 0);
            msk[o] |= tmp;
        }
        int ans = 0;
        for(int i = 0; i < maxd; ++i)
            for(int j = 0; j < maxd; ++j)
                ans += (msk[i] >> j) & 1;
        return ans;
    }
};
