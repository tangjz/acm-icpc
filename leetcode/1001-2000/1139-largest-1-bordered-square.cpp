class Solution {
public:
    int largest1BorderedSquare(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int> > pL(n, vector<int>(m)), pU(n, vector<int>(m));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                pL[i][j] = grid[i][j] ? (j > 0 ? pL[i][j - 1] : j) : j + 1;
                pU[i][j] = grid[i][j] ? (i > 0 ? pU[i - 1][j] : i) : i + 1;
            }
        int ans = 0;
        for(int i = 0; i < n - ans; ++i)
            for(int j = 0; j < m - ans; ++j)
                for(int k = min(n - i, m - j); k > ans; --k) {
                    int iR = i + k - 1, jR = j + k - 1;
                    if(pL[iR][jR] <= j && pU[iR][jR] <= i && pL[i][jR] <= j && pU[iR][j] <= i)
                        ans = k;
                }
        return ans * ans;
    }
};
