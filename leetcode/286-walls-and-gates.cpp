class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        int n = rooms.size(), m = rooms[0].size();
        queue<pair<int, int> > que;
        auto upd = [&](int x, int y, int d) {
            if(x < 0 || x >= n || y < 0 || y >= m || rooms[x][y] <= d)
                return;
            rooms[x][y] = d;
            que.push({x, y});
        };
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                if(!rooms[i][j])
                    que.push({i, j});
        while(!que.empty()) {
            int x, y;
            tie(x, y) = que.front();
            que.pop();
            int d = rooms[x][y] + 1;
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    if(!dx == !dy)
                        continue;
                    upd(x + dx, y + dy, d);
                }
        }
    }
};
