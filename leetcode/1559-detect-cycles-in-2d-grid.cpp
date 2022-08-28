class Solution {
    void dfs(int x, int y, vector<vector<char> > &grid, vector<vector<int> > &vis, int n, int m, int &cntV, int &cntE) {
        vis[x][y] = 1;
        ++cntV;
        for(int dx = -1; dx <= 1; ++dx)
            for(int dy = -1; dy <= 1; ++dy) {
                if(!dx == !dy)
                    continue;
                int nx = x + dx, ny = y + dy;
                if(nx < 0 || nx >= n || ny < 0 || ny >= m || grid[x][y] != grid[nx][ny])
                    continue;
                ++cntE;
                if(!vis[nx][ny])
                    dfs(nx, ny, grid, vis, n, m, cntV, cntE);
            }
    }
public:
    bool containsCycle(vector<vector<char>>& grid) {
        int n = (int)grid.size(), m = (int)grid[0].size();
        vector<vector<int> > vis(n, vector<int>(m, 0));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                if(vis[i][j])
                    continue;
                int cntV = 0, cntE = 0;
                dfs(i, j, grid, vis, n, m, cntV, cntE);
                cntE >>= 1;
                if(cntV <= cntE)
                    return 1;
            }
        return 0;
    }
};
