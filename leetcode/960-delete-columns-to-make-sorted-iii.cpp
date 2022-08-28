class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        int n = strs.size(), m = 0;
        vector<int> len(n);
        for(int i = 0; i < n; ++i) {
            len[i] = strs[i].size();
            m = max(m, len[i]);
        }
        int ans = m;
        vector<int> dp(m, m);
        for(int i = 0; i < m; ++i) {
            dp[i] = min(dp[i], i);
            for(int j = 0; j < i; ++j) {
                bool skp = 0;
                for(int k = 0; !skp && k < n; ++k)
                    skp |= i < len[k] && strs[k][j] > strs[k][i];
                if(!skp)
                    dp[i] = min(dp[i], dp[j] + i - j - 1);
            }
            ans = min(ans, dp[i] + (m - 1 - i));
        }
        return ans;
    }
};
