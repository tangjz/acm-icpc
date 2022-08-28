class Solution {
public:
    int longestLine(vector<vector<int>>& mat) {
        const int maxd = 4, dx[] = {0, -1, -1, -1}, dy[] = {-1, -1, 0, 1};
        int n = mat.size(), m = mat[0].size();
        vector<vector<vector<int> > > dp(maxd, vector<vector<int> >(n, vector<int>(m)));
        int ans = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                if(!mat[i][j])
                    continue;
                for(int d = 0; d < maxd; ++d) {
                    int x = i + dx[d], y = j + dy[d];
                    if(x >= 0 && y >= 0 && y < m)
                        dp[d][i][j] = dp[d][x][y];
                    ans = max(ans, ++dp[d][i][j]);
                }
            }
        return ans;
    }
};
