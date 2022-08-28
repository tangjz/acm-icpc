class Solution {
public:
    int numberOfWays(string seq) {
        const int mod = (int)1e9 + 7;
        int n = seq.size();
        vector<int> dp(n + 1), ctr(n + 1);
        dp[0] = ctr[0] = 1;
        for(int i = 1, c = 0; i <= n; ++i) {
            c += seq[i - 1] == 'S';
            if(c >= 2)
                dp[i] = ctr[c - 2];
            (ctr[c] += dp[i]) >= mod && (ctr[c] -= mod);
        }
        return dp.back();
    }
};
