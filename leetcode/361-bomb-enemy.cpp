class Solution {
public:
    int maxKilledEnemies(vector<vector<char>>& grid) {
        int r = grid.size(), c = grid[0].size(), n = r * c;
        vector<int> f(n);
        for(int i = 0; i < r; ++i)
            for(int j = 0, k; j < c; ++j) {
                if(grid[i][j] == 'W')
                    continue;
                int ctr = 0;
                for(k = j; k < c && grid[i][k] != 'W'; ++k)
                    ctr += grid[i][k] == 'E';
                for(int u = i * c + j; j < k; ++j, ++u)
                    if(grid[i][j] == '0')
                        f[u] += ctr;
            }
        for(int i = 0; i < c; ++i)
            for(int j = 0, k; j < r; ++j) {
                if(grid[j][i] == 'W')
                    continue;
                int ctr = 0;
                for(k = j; k < r && grid[k][i] != 'W'; ++k)
                    ctr += grid[k][i] == 'E';
                for(int u = j * c + i; j < k; ++j, u += c)
                    if(grid[j][i] == '0')
                        f[u] += ctr;
            }
        return *max_element(f.begin(), f.end());
    }
};
