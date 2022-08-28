class Solution {
public:
    long long minCostToTravelOnDays(vector<int>& days, vector<vector<int>>& tickets) {
        typedef long long LL;
        int n = days.size();
        vector<LL> dp(n + 1, LLONG_MAX);
        set<pair<LL, int> > suf;
        dp[0] = 0;
        for(int i = 0; i < n; ++i) {
            int sta = days[i];
            while(!suf.empty() && suf.begin() -> second <= i)
                suf.erase(suf.begin());
            if(!suf.empty())
                dp[i] = min(dp[i], suf.begin() -> first);
            // printf("dp %d: %lld\n", i, dp[i]);
            if(dp[i] == LLONG_MAX)
                continue;
            for(auto &it: tickets) {
                int end = sta + it[0];
                int j = lower_bound(days.begin() + i, days.end(), end) - days.begin();
                LL tmp = dp[i] + it[1];
                if(tmp < dp[j]) {
                    // printf("%d -> %d: %lld\n", i, j, tmp);
                    suf.erase({dp[j], j});
                    dp[j] = tmp;
                    suf.insert({dp[j], j});
                }
            }
        }
        return dp[n];
    }
};
