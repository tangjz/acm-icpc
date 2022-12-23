class Solution {
public:
    bool isThereAPath(vector<vector<int>>& grid) {
        int r = grid.size(), c = grid[0].size();
        if((r + c - 1) & 1)
            return 0;
        vector<vector<pair<int, int> > > dp(r, vector<pair<int, int> >(c));
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j) {
                int L = INT_MAX, R = INT_MIN;
                if(!i && !j) {
                    L = R = 0;
                } else if(!i) {
                    tie(L, R) = dp[i][j - 1];
                } else if(!j) {
                    tie(L, R) = dp[i - 1][j];
                } else {
                    L = min(dp[i][j - 1].first, dp[i - 1][j].first);
                    R = max(dp[i][j - 1].second, dp[i - 1][j].second);
                }
                if(grid[i][j]) {
                    ++L;
                    ++R;
                } else {
                    --L;
                    --R;
                }
                dp[i][j] = {L, R};
            }
        return dp[r - 1][c - 1].first <= 0 && 0 <= dp[r - 1][c - 1].second;
    }
};
