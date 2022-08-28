class Solution {
public:
    bool canIWin(int n, int m) {
        if(!m)
            return 1;
        if(m > n * (n + 1) / 2)
            return 0;
        vector<bool> dp(1 << n);
        for(int i = (1 << n) - 1; i >= 0; --i) {
            int sum = 0;
            bool win = 0;
            for(int j = 0; j < n; ++j)
                if((i >> j) & 1) {
                    sum += j + 1;
                } else {
                    win |= !dp[i | 1 << j];
                }
            dp[i] = sum < m && win;
        }
        return dp[0];
    }
};
