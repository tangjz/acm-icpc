class Solution {
    void upd_max(int &x, int y) {
        x < y && (x = y);
    }
public:
    int maxGroupNumber(vector<int>& tiles) {
        int n = tiles.size();
        sort(tiles.begin(), tiles.end());
        static int f[2][3][5], cur = 0, pre = 1;
        memset(f[cur], -1, sizeof(f[0]));
        f[cur][0][0] = 0;
        for(int i = 0, c; i < n; ) {
            for(++i, c = 1; i < n && tiles[i - 1] == tiles[i]; ++i, ++c);
            // printf("state %d: %d %d\n", i, tiles[i - 1], c);
            swap(cur, pre);
            memset(f[cur], -1, sizeof(f[0]));
            for(int x = 0; x < 3; ++x)
                for(int y = 0; y < 5; ++y) {
                    if(f[pre][x][y] == -1)
                        continue;
                    // printf("check %d %d for %d %d\n", x, y, tiles[i - 1], c);
                    for(int p = min(min(x, y), c); p >= 0; --p) {
                        int q = (c - p) / 3;
                        upd_max(f[cur][min(y - p, 2)][min(c - p - q * 3, 4)], f[pre][x][y] + p + q);
                        if(q > 0) {
                            --q;
                            upd_max(f[cur][min(y - p, 2)][min(c - p - q * 3, 4)], f[pre][x][y] + p + q);
                        }
                    }
                }
            // for(int x = 0; x < 3; ++x)
            //     for(int y = 0; y < 5; ++y)
            //         if(f[cur][x][y] != -1)
            //             printf("%d %d %d: %d\n", tiles[i - 1], x, y, f[cur][x][y]);
            if(i == n || tiles[i - 1] + 1 == tiles[i])
                continue;
            // printf("move %d -> %d\n", tiles[i - 1], tiles[i]);
            if(tiles[i - 1] + 2 == tiles[i]) {
                swap(cur, pre);
                memset(f[cur], -1, sizeof(f[0]));
                for(int x = 0; x < 3; ++x)
                    for(int y = 0; y < 5; ++y)
                        upd_max(f[cur][min(y, 2)][0], f[pre][x][y]);
            } else {
                swap(cur, pre);
                memset(f[cur], -1, sizeof(f[0]));
                for(int x = 0; x < 3; ++x)
                    for(int y = 0; y < 5; ++y)
                        upd_max(f[cur][0][0], f[pre][x][y]);
            }
        }
        int ans = 0;
        for(int x = 0; x < 3; ++x)
            for(int y = 0; y < 5; ++y)
                upd_max(ans, f[cur][x][y]);
        return ans;
    }
};
