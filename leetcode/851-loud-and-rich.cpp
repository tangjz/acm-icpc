class Solution {
public:
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
        int n = quiet.size();
        vector<vector<int> > e(n);
        vector<int> deg(n), dp(n);
        queue<int> que;
        for(auto &it: richer) {
            e[it[0]].push_back(it[1]);
            ++deg[it[1]];
        }
        for(int i = 0; i < n; ++i) {
            dp[i] = i;
            if(!deg[i])
                que.push(i);
        }
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            for(int v: e[u]) {
                if(quiet[dp[u]] < quiet[dp[v]])
                    dp[v] = dp[u];
                if(!(--deg[v]))
                    que.push(v);
            }
        }
        return dp;
    }
};
