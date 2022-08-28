class Solution {
    int solve(int u, vector<int> &dp, vector<vector<int> > &e, vector<int> &c) {
        if(dp[u] >= 0)
            return dp[u];
        int best = 0;
        for(int v: e[u]) {
            best = max(best, solve(v, dp, e, c));
        }
        // printf("solve %d: %d\n", u, best + c[u]);
        return dp[u] = best + c[u];
    }
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        vector<int> dp(n, -1);
        vector<vector<int> > e(n);
        for(auto &it: relations) {
            e[--it[1]].push_back(--it[0]);
        }
        int ans = 0;
        for(int i = 0; i < n; ++i)
            ans = max(ans, solve(i, dp, e, time));
        return ans;
    }
};
