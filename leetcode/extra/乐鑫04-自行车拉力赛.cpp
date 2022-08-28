class Solution {
public:
    int minSupplyTimes(int lim, int sta, vector<vector<int>>& pos) {
        int las = 0;
        vector<int> dp = {sta};
        pos.push_back({lim, 0});
        for(auto &it: pos) {
            dp.push_back(-1);
            for(int &x: dp)
                (x -= it[0] - las) < 0 && (x = -1);
            int n = dp.size();
            for(int i = n - 1; i > 0; --i)
                if(dp[i - 1] >= 0)
                    dp[i] = max(dp[i], min(dp[i - 1] + it[1], lim + 1));
            las = it[0];
        }
        int n = dp.size();
        for(int i = 0; i < n; ++i)
            if(dp[i] >= 0)
                return i;
        return -1;
    }
};
