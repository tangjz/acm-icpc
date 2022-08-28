class Solution {
public:
    vector<vector<int>> bicycleYard(vector<int>& position, vector<vector<int>>& terrain, vector<vector<int>>& obstacle) {
        static const int maxn = 103;
        static int st = 0, tim[maxn][maxn][maxn] = {};
        if(!(++st)) {
            memset(tim, 0, sizeof(tim));
            ++st;
        }
        int r = (int)terrain.size(), c = (int)terrain[0].size();
        vector<vector<int> > ret;
        queue<vector<int> > que;
        auto upd = [&](int x, int y, int w) {
            if(x < 0 || x >= r || y < 0 || y >= c)
                return;
            w -= terrain[x][y] + obstacle[x][y];
            if(w <= 0 || tim[x][y][w] == st)
                return;
            tim[x][y][w] = st;
            que.push({x, y, w});
        };
        int sx = position[0], sy = position[1];
        upd(sx, sy, 1 + terrain[sx][sy] + obstacle[sx][sy]);
        while(!que.empty()) {
            vector<int> cur = move(que.front());
            que.pop();
            int x = cur[0], y = cur[1], w = cur[2] + terrain[x][y];
            if(cur[2] == 1 && !(x == sx && y == sy))
                ret.push_back({x, y});
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    if(!dx == !dy)
                        continue;
                    upd(x + dx, y + dy, w);
                }
        }
        sort(ret.begin(), ret.end());
        return ret;
    }
};
