class Solution {
public:
    int countSpecialSubsequences(vector<int>& nums) {
        const int mod = (int)1e9 + 7;
        int dp[2][3] = {}, cur = 0, pre = 1;
        for(int x: nums) {
            swap(cur, pre);
            for(int i = 0; i < 3; ++i) {
                dp[cur][i] = dp[pre][i];
                if(x == i) {
                    (dp[cur][i] += dp[pre][i]) >= mod && (dp[cur][i] -= mod);
                    if(i > 0) {
                        (dp[cur][i] += dp[pre][i - 1]) >= mod && (dp[cur][i] -= mod);
                    } else {
                        (dp[cur][i] += 1) >= mod && (dp[cur][i] -= mod);
                    }
                }
            }
        }
        return dp[cur][2];
    }
};
