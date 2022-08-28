class Solution {
public:
    vector<vector<int>> allCellsDistOrder(int rows, int cols, int rCenter, int cCenter) {
        vector<vector<bool> > vis(rows, vector<bool>(cols));
        vector<vector<int> > que;
        auto append = [&](int x, int y) {
            if(x < 0 || x >= rows || y < 0 || y >= cols || vis[x][y])
                return;
            vis[x][y] = 1;
            que.push_back({x, y});
        };
        append(rCenter, cCenter);
        for(int i = 0; i < (int)que.size(); ++i) {
            int x = que[i][0], y = que[i][1];
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    if(!dx == !dy)
                        continue;
                    append(x + dx, y + dy);
                }
        }
        return que;
    }
};
