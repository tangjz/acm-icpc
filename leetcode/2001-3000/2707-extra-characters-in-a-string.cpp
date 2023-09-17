class Solution {
public:
    int minExtraChar(string s, vector<string>& dic) {
        int n = s.size();
        vector<unordered_set<string> > vis(n + 1);
        for(auto &it: dic) {
            int m = it.size();
            if(vis.size() <= m)
                continue;
            vis[m].insert(it);
        }
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for(int i = 0; i < n; ++i) {
            dp[i + 1] = min(dp[i + 1], dp[i] + 1);
            string t = "";
            for(int j = i; j < n; ++j) {
                t.push_back(s[j]);
                if(vis[j - i + 1].count(t))
                    dp[j + 1] = min(dp[j + 1], dp[i]);
            }
        }
        return dp[n];
    }
};
