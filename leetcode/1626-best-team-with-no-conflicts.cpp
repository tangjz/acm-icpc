class Solution {
public:
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        int n = scores.size();
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return make_pair(ages[u], scores[u]) < make_pair(ages[v], scores[v]);
        });
        int ans = 0;
        vector<int> dp(n + 1);
        for(int i = 0; i < n; ++i) {
            dp[i] = max(dp[i], scores[ord[i]]);
            for(int j = 0; j < i; ++j)
                if(scores[ord[j]] <= scores[ord[i]])
                    dp[i] = max(dp[i], dp[j] + scores[ord[i]]);
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};
