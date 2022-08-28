class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        if(grid.front().front() || grid.back().back())
            return -1;
        int n = grid.size();
        vector<vector<int> > dis(n, vector<int>(n, -1));
        queue<pair<int, int> > que;
        auto upd = [&](int x, int y, int d) {
            if(x < 0 || x >= n || y < 0 || y >= n || grid[x][y] || dis[x][y] != -1)
                return;
            dis[x][y] = d;
            que.push({x, y});
        };
        upd(0, 0, 1);
        while(!que.empty()) {
            int x, y;
            tie(x, y) = que.front();
            que.pop();
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy)
                    upd(x + dx, y + dy, dis[x][y] + 1);
        }
        return dis.back().back();
    }
};
