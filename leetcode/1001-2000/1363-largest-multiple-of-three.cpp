class Solution {
public:
    string largestMultipleOfThree(vector<int>& digits) {
        int n = (int)digits.size();
        sort(digits.begin(), digits.end());
        vector<vector<int> > dp(n + 1, vector<int>(3, INT_MIN));
        dp[0][0] = 0;
        for(int i = 0; i < n; ++i) {
            int sft = digits[i] % 3;
            for(int j = 0, k = sft; j < 3; ++j, (++k) == 3 && (k = 0)) {
                dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
                dp[i + 1][k] = max(dp[i + 1][k], dp[i][j] + 1);
            }
        }
        string ret = "";
        for(int i = n - 1, pos = 0; i >= 0; --i) {
            int sft = digits[i] % 3, pre = (pos + 3 - sft) % 3;
            if(dp[i][pre] + 1 == dp[i + 1][pos]) {
                ret += '0' + digits[i];
                pos = pre;
            }
        }
        int sta = 0;
        for(int len = (int)ret.size(); sta + 1 < len && ret[sta] == '0'; ++sta);
        return ret.substr(sta);
    }
};
