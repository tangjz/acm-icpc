class Solution {
public:
    int maximumANDSum(vector<int>& nums, int m) {
        vector<int> pw = {1};
        for(int i = 1; i <= m; ++i) {
            pw.push_back(pw.back() * 3);
        }
        vector<int> dp(pw.back());
        for(int x: nums) {
            for(int i = pw.back() - 1; i >= 0; --i) {
                for(int j = 0, tmp = i; j < m; ++j, tmp /= 3) {
                    int cnt = tmp % 3;
                    if(cnt < 2) {
                        int ii = i + pw[j];
                        dp[ii] = max(dp[ii], dp[i] + (x & (j + 1)));
                    }
                }
            }
        }
        return dp.back();
    }
};
