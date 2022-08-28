class Solution {
public:
    int countRoutes(vector<int>& locations, int start, int finish, int fuel) {
        const int mod = (int)1e9 + 7;
        int ans = 0, n = (int)locations.size();
        vector<vector<int> > dp(fuel + 1, vector<int>(n, 0));
        dp[fuel][start] = 1;
        for(int i = fuel; i >= 0; --i) {
            (ans += dp[i][finish]) >= mod && (ans -= mod);
            for(int j = 0; j < n; ++j) {
                if(!dp[i][j])
                    continue;
                for(int k = 0; k < n; ++k) {
                    if(j == k)
                        continue;
                    int nxt = i - abs(locations[j] - locations[k]);
                    if(nxt < 0)
                        continue;
                    (dp[nxt][k] += dp[i][j]) >= mod && (dp[nxt][k] -= mod);
                }
            }
        }
        return ans;
    }
};
