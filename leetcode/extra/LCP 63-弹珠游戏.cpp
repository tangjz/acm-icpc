class Solution {
public:
    vector<vector<int>> ballGame(int num, vector<string>& plate) {
        static const int maxd = 4, dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
        static const int maxn = (int)4e6 + 1;
        int r = plate.size(), c = plate[0].size(), n = r * c * 4, tot = 0;
        num = min(num, r * c - 1);
        static int dis[maxn], que[maxn];
        memset(dis, 0x3f, n * sizeof(int));
        for(int x = 0; x < r; ++x)
            for(int y = 0; y < c; ++y) {
                if(plate[x][y] != 'O')
                    continue;
                int u = (x * c + y) << 2;
                for(int d = 0; d < maxd; ++d, ++u) {
                    dis[u] = 0;
                    que[tot++] = u;
                }
            }
        for(int i = 0; i < tot; ++i) {
            int u = que[i];
            int tmp = u >> 2, ux = tmp / c, uy = tmp % c, ud = u & 3;
            int vx = ux - dx[ud], vy = uy - dy[ud], vd = ud;
            if(vx < 0 || vx >= r || vy < 0 || vy >= c || plate[vx][vy] == 'O')
                continue;
            if(plate[vx][vy] == 'W') {
                (++vd) > 3 && (vd = 0);
            } else if(plate[vx][vy] == 'E') {
                (--vd) < 0 && (vd = 3);
            }
            int v = (vx * c + vy) << 2 | vd;
            if(dis[v] > dis[u] + 1) {
                dis[v] = dis[u] + 1;
                que[tot++] = v;
            }
        }
        vector<vector<int> > ret;
        for(int i = 1; i + 1 < c; ++i) {
            if(plate[0][i] == '.' && dis[(0 * c + i) << 2 | 2] <= num)
                ret.push_back({0, i});
            if(plate[r - 1][i] == '.' && dis[((r - 1) * c + i) << 2 | 0] <= num)
                ret.push_back({r - 1, i});
        }
        for(int i = 1; i + 1 < r; ++i) {
            if(plate[i][0] == '.' && dis[(i * c + 0) << 2 | 1] <= num)
                ret.push_back({i, 0});
            if(plate[i][c - 1] == '.' && dis[(i * c + c - 1) << 2 | 3] <= num)
                ret.push_back({i, c - 1});
        }
        return ret;
    }
};
