class Solution {
public:
    long long maxScore(vector<vector<int>>& edges) {
        typedef long long LL;
        int n = edges.size();
        vector<vector<int> > e(n);
        for(int i = 1; i < n; ++i)
            e[edges[i][0]].push_back(i);
        vector<pair<LL, LL> > dp(n, {-1LL, -1LL});
        function<pair<LL, LL>(int)> calc = [&](int u) -> pair<LL, LL> {
            if(dp[u].first >= 0)
                return dp[u];
            LL upp = LLONG_MIN;
            pair<LL, LL> ret;
            for(int v: e[u]) {
                pair<LL, LL> tmp = calc(v);
                LL best = max(tmp.first, tmp.second);
                ret.second += best;
                upp = max(upp, tmp.second + edges[v][1] - best);
            }
            ret.first = upp == LLONG_MIN ? upp : ret.second + upp;
            return dp[u] = ret;
        };
        pair<LL, LL> ret = calc(0);
        return max(ret.first, ret.second);
    }
};
