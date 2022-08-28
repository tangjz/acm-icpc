class Solution {
public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int> > rsum = grid, csum = grid;
        for(int i = 0; i < n; ++i)
            for(int j = 1; j < m; ++j)
                rsum[i][j] += rsum[i][j - 1];
        for(int i = 1; i < n; ++i)
            for(int j = 0; j < m; ++j)
                csum[i][j] += csum[i - 1][j];
        for(int k = min(n, m); k > 1; --k) {
            for(int i = 0; i <= n - k; ++i)
                for(int j = 0; j <= m - k; ++j) {
                    int sum = rsum[i][j + k - 1] - (j ? rsum[i][j - 1] : 0);
                    int sumL = 0, sumR = 0;
                    bool chk = true;
                    for(int x = 0; chk && x < k; ++x) {
                        chk &= rsum[i + x][j + k - 1] - (j ? rsum[i + x][j - 1] : 0) == sum;
                        chk &= csum[i + k - 1][j + x] - (i ? csum[i - 1][j + x] : 0) == sum;
                        sumL += grid[i + x][j + x];
                        sumR += grid[i + x][j + k - 1 - x];
                    }
                    chk &= sumL == sum && sumR == sum;
                    if(chk)
                        return k;
                }
        }
        return 1;
    }
};
