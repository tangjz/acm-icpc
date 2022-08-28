class Solution {
public:
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        int ans = 0;
        int n = grid1.size(), m = grid1[0].size();
        vector<vector<bool> > vis(n, vector<bool>(m));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                if(!grid2[i][j] || vis[i][j])
                    continue;
                int ctr = 0;
                vector<pair<int, int> > que;
                vis[i][j] = 1;
                que.push_back({i, j});
                for(int k = 0; k < (int)que.size(); ++k) {
                    int x, y;
                    tie(x, y) = que[k];
                    ctr += grid1[x][y] == 1;
                    for(int dx = -1; dx <= 1; ++dx)
                        for(int dy = -1; dy <= 1; ++dy) {
                            if(!!dx == !!dy)
                                continue;
                            int xx = x + dx, yy = y + dy;
                            if(xx < 0 || xx >= n || yy < 0 || yy >= m || !grid2[xx][yy] || vis[xx][yy])
                                continue;
                            vis[xx][yy] = 1;
                            que.push_back({xx, yy});
                        }
                }
                ans += ctr == (int)que.size();
            }
        return ans;
    }
};
