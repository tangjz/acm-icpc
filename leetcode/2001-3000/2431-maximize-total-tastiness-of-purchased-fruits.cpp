class Solution {
public:
    int maxTastiness(vector<int>& c, vector<int>& w, int V, int A) {
        int n = c.size();
        vector<vector<int> > dp(A + 1, vector<int>(V + 1));
        for(int i = 0; i < n; ++i) {
            int one = c[i], half = one / 2;
            for(int j = A; j >= 0; --j)
                for(int k = V; k >= 0; --k) {
                    int nxt = dp[j][k];
                    if(k >= one)
                        nxt = max(nxt, dp[j][k - one] + w[i]);
                    if(j > 0 && k >= half)
                        nxt = max(nxt, dp[j - 1][k - half] + w[i]);
                    dp[j][k] = nxt;
                }
        }
        return dp[A][V];
    }
};
