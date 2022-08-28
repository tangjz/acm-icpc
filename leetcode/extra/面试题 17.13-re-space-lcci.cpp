class Solution {
public:
    int respace(vector<string>& dictionary, string sentence) {
        int n = sentence.size();
        vector<unordered_set<string> > vis(n + 1);
        for(auto &it: dictionary)
            if(it.size() <= n)
                vis[it.size()].insert(it);
        vector<int> dp(n + 1, n + 1);
        dp[0] = 0;
        for(int i = 0; i < n; ++i) {
            string sub = "";
            for(int j = i + 1; j <= n; ++j) {
                sub.push_back(sentence[j - 1]);
                dp[j] = min(dp[j], dp[i] + (vis[j - i].count(sub) ? 0 : j - i));
            }
        }
        return dp[n];
    }
};
