class Solution {
public:
    int minimumWhiteTiles(string floor, int m, int l) {
        int n = floor.size();
        vector<vector<int> > f(n + 1, vector<int>(m + 1, n + 1));
        for(int i = 0; i <= m; ++i)
            f[0][i] = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j <= m; ++j) {
                f[i + 1][j] = min(f[i + 1][j], f[i][j] + (floor[i] == '1'));
                if(j < m)
                    f[min(i + l, n)][j + 1] = min(f[min(i + l, n)][j + 1], f[i][j]);
            }
        return f[n][m];
    }
};
