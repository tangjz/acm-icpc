class Solution {
public:
    bool possibleToStamp(vector<vector<int>>& grid, int r, int c) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int> > psum(n + 1, vector<int>(m + 1)), res(n + 1, vector<int>(m + 1));
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j) {
                psum[i][j] = psum[i][j - 1] + grid[i - 1][j - 1];
            }
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j) {
                psum[i][j] += psum[i - 1][j];
            }
        for(int i = r; i <= n; ++i)
            for(int j = c; j <= m; ++j) {
                int cnt = psum[i][j] - psum[i - r][j] - psum[i][j - c] + psum[i - r][j - c];
                if(cnt > 0)
                    continue;
                ++res[i - r][j - c];
                --res[i - r][j];
                --res[i][j - c];
                ++res[i][j];
            }
        for(int i = 0; i < n; ++i)
            for(int j = 1; j < m; ++j) {
                res[i][j] += res[i][j - 1];
            }
        for(int i = 1; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                res[i][j] += res[i - 1][j];
            }
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                if(!grid[i][j] && !res[i][j])
                    return false;
        return true;
    }
};
