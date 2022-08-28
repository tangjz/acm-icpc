class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        const int dt[3] = {1, 7, 30};
        int n = days.size();
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for(int i = 0; i < n; ++i) {
            if(dp[i] == INT_MAX)
                continue;
            for(int j = i; j < n; ++j) {
                bool upd = 0;
                int dif = days[j] - days[i] + 1;
                for(int k = 0; k < 3; ++k) {
                    if(dif > dt[k])
                        continue;
                    upd = 1;
                    dp[j + 1] = min(dp[j + 1], dp[i] + costs[k]);
                }
                if(!upd)
                    break;
            }
        }
        return dp.back();
    }
};
