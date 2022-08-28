class Solution {
public:
    vector<vector<int>> highestRankedKItems(vector<vector<int>>& grid, vector<int>& pricing, vector<int>& start, int k) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int> > dis(n, vector<int>(m)), que, items;
        int sx = start[0], sy = start[1];
        dis[sx][sy] = 1;
        que.push_back({sx, sy});
        for(int i = 0; i < (int)que.size(); ++i) {
            auto &vec = que[i];
            int x = vec[0], y = vec[1];
            if(pricing[0] <= grid[x][y] && grid[x][y] <= pricing[1]) {
                items.push_back({dis[x][y], grid[x][y], x, y});
            }
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    if(!!dx == !!dy)
                        continue;
                    int xx = x + dx, yy = y + dy;
                    if(xx < 0 || xx >= n || yy < 0 || yy >= m || !grid[xx][yy] || dis[xx][yy])
                        continue;
                    dis[xx][yy] = dis[x][y] + 1;
                    que.push_back({xx, yy});
                }
        }
        sort(items.begin(), items.end());
        vector<vector<int> > ret;
        for(int i = 0; i < (int)items.size() && i < k; ++i)
            ret.push_back({items[i][2], items[i][3]});
        return ret;
    }
};
