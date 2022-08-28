class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size(), m = 1 << n;
        vector<vector<int> > dp(n, vector<int>(m));
        queue<pair<int, int> > que;
        auto upd = [&](int s, int msk, int d) {
            if(dp[s][msk])
                return;
            dp[s][msk] = d;
            que.push({s, msk});
            return;
        };
        for(int i = 0; i < n; ++i)
            upd(i, 1 << i, 1);
        while(!que.empty()) {
            int s, msk;
            tie(s, msk) = que.front();
            que.pop();
            for(int t: graph[s]) {
                int nxt = msk | (1 << t);
                if(nxt == m - 1)
                    return dp[s][msk];
                upd(t, nxt, dp[s][msk] + 1);
            }
        }
        return 0;
    }
};
