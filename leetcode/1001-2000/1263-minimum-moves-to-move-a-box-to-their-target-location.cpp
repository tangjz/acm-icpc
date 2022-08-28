class Solution {
public:
    int minPushBox(vector<vector<char>>& grid) {
        const int maxn = 21, INF = 0x3f3f3f3f;
        int n = (int)grid.size(), m = (int)grid[0].size();
        static int dis[maxn][maxn][maxn][maxn];
        int sx, sy, bx, by, tx, ty;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                if(grid[i][j] == 'S') {
                    tie(sx, sy) = {i, j};
                    grid[i][j] = '.';
                } else if(grid[i][j] == 'B') {
                    tie(bx, by) = {i, j};
                    grid[i][j] = '.';
                } else if(grid[i][j] == 'T') {
                    tie(tx, ty) = {i, j};
                    grid[i][j] = '.';
                }
                for(int k = 0; k < n; ++k)
                    memset(dis[i][j][k], 0x3f, m * sizeof(int));
            }
        vector<vector<int> > que;
        auto valid = [&](int x, int y) {
            return x >= 0 && x < n && y >= 0 && y < m && grid[x][y] == '.';
        };
        auto get = [&](vector<int> const &key) -> int& {
            int sx = key[0], sy = key[1], bx = key[2], by = key[3];
            return dis[sx][sy][bx][by];
        };
        auto append = [&](vector<int> const &key, int val) {
            int sx = key[0], sy = key[1], bx = key[2], by = key[3];
            if(valid(sx, sy) && valid(bx, by) && !(sx == bx && sy == by)) {
                int &info = get(key);
                if(val < info) {
                    que.push_back(key);
                    info = val;
                }
            }
        };
        append({sx, sy, bx, by}, 0);
        for(int i = 0, j; i < (int)que.size(); ) {
            int curDist = get(que[i]);
            for(j = i; j < (int)que.size() && curDist == get(que[j]); ++j) {
                vector<int> cur = que[j];
                if(cur[2] == tx && cur[3] == ty)
                    return curDist;
                for(int dx = -1; dx <= 1; ++dx)
                    for(int dy = -1; dy <= 1; ++dy) {
                        if(!dx == !dy)
                            continue;
                        vector<int> nxt(cur.begin(), cur.end());
                        nxt[0] += dx;
                        nxt[1] += dy;
                        append(nxt, curDist);
                    }
            }
            for( ; i < j; ++i) {
                vector<int> cur = que[i];
                for(int dx = -1; dx <= 1; ++dx)
                    for(int dy = -1; dy <= 1; ++dy) {
                        if(!dx == !dy)
                            continue;
                        if(cur[0] + dx == cur[2] && cur[1] + dy == cur[3]) {
                            vector<int> nxt(cur.begin(), cur.end());
                            nxt[0] += dx;
                            nxt[1] += dy;
                            nxt[2] += dx;
                            nxt[3] += dy;
                            append(nxt, curDist + 1);
                        }
                    }
            }
        }
        return -1;
    }
};
