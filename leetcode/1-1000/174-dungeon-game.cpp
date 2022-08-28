class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int r = (int)dungeon.size();
        if(!r)
            return 0;
        int c = (int)dungeon[0].size();
        if(!c)
            return 0;
        typedef long long LL;
        vector<LL> dp(c);
        dp[c - 1] = 1 - min(dungeon[r - 1][c - 1], 0);
        for(int j = c - 2; j >= 0; --j)
            dp[j] = max(dp[j + 1] - dungeon[r - 1][j], 1LL);
        for(int i = r - 2; i >= 0; --i) {
            dp[c - 1] = max(dp[c - 1] - dungeon[i][c - 1], 1LL);
            for(int j = c - 2; j >= 0; --j)
                dp[j] = max(min(dp[j], dp[j + 1]) - dungeon[i][j], 1LL);
        }
        return dp[0];
    }
};
