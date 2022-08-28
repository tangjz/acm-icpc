class Solution {
    void upd_min(int &x, int y) {
        x > y && (x = y);
    }
public:
    int getLengthOfOptimalCompression(string s, int k) {
        int n = (int)s.size();
        vector<int> cost(n + 1);
        cost[1] = 1;
        for(int i = 2; i <= n; ++i)
            cost[i] = (int)to_string(i).size() + 1;
        vector<vector<int> > dp(n + 1, vector<int>(k + 1, INT_MAX));
        for(int i = 0; i <= k; ++i)
            dp[0][i] = 0;
        for(int L = 0; L < n; ++L) {
            for(int i = 1; i <= k; ++i)
                upd_min(dp[L + 1][i], dp[L][i - 1]);
            for(int R = L, len = 0, skp = 0; R < n; ++R) {
                ++len;
                skp += s[L] != s[R];
                if(skp > k)
                    break;
                for(int i = skp; i <= k; ++i)
                    upd_min(dp[R + 1][i], dp[L][i - skp] + cost[len - skp]);
            }
        }
        return dp[n][k];
    }
};
