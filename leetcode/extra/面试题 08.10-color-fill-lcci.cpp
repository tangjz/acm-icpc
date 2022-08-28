class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& grid, int row, int col, int color) {
        int n = grid.size(), m = grid[0].size(), ori = grid[row][col];
        vector<pair<int, int> > que;
        auto get = [&](int x, int y) {
            if(x < 0 || x >= n || y < 0 || y >= m)
                return -1;
            return grid[x][y];
        };
        auto append = [&](int x, int y) {
            grid[x][y] = -1;
            que.push_back({x, y});
        };
        append(row, col);
        for(int i = 0; i < (int)que.size(); ++i) {
            int x, y;
            tie(x, y) = que[i];
            for(int dx = -1; dx <= 1; ++dx) {
                for(int dy = -1; dy <= 1; ++dy) {
                    if(!dx == !dy)
                        continue;
                    int xx = x + dx, yy = y + dy;
                    int cur = get(xx, yy);
                    if(cur == ori)
                        append(xx, yy);
                }
            }
        }
        for(int i = 0; i < (int)que.size(); ++i) {
            int x, y;
            tie(x, y) = que[i];
            grid[x][y] = color;
        }
        return grid;
    }
};
