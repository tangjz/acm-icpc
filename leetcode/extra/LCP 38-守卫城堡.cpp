class Solution {
    int calc(vector<string> &grid) {
        static const int INF = 0x3f3f3f3f;
        int n = grid[0].size();
        static int f[2][3][3], cur = 0, pre = 1;
        static int init = 0, tr[3][3][4][4][3];
        if(!init) {
            for(int u0 = 0; u0 < 3; ++u0) // 0: block, 1: C, 2: S
                for(int u1 = 0; u1 < 3; ++u1)
                    for(int w0 = 0; w0 < 4; ++w0) // 0: block, 1: C, 2: S, 3: empty
                        for(int w1 = 0; w1 < 4; ++w1) {
                            int v0 = w0, v1 = w1, adt = 0;
                            if(u0 + u1 == 3) {
                                v0 = v1 = 0;
                                adt = INF;
                            } else {
                                if(v0 && u0) {
                                    if(v0 + u0 == 3)
                                        adt = INF;
                                    v0 = u0;
                                }
                                if(v1 && u1) {
                                    if(v1 + u1 == 3)
                                        adt = INF;
                                    v1 = u1;
                                }
                                if(v0 == 3 && v1 == 3) {
                                    v0 = v1 = 0;
                                } else if(v0 == 3) {
                                    v0 = v1;
                                } else if(v1 == 3) {
                                    v1 = v0;
                                }
                                if(v0 + v1 == 3)
                                    adt = INF;
                            }
                            tr[u0][u1][w0][w1][0] = v0;
                            tr[u0][u1][w0][w1][1] = v1;
                            tr[u0][u1][w0][w1][2] = adt;
                        }
            init = 1;
        }
        memset(f[cur], 0x3f, sizeof(f[0]));
        f[cur][0][0] = 0;
        for(int i = 0; i < n; ++i) {
            swap(cur, pre);
            memset(f[cur], 0x3f, sizeof(f[0]));
            vector<int> cand[2];
            for(int j = 0; j < 2; ++j)
                switch(grid[j][i]) {
                    case '.': {
                        cand[j].push_back(3);
                    }
                    case '#': {
                        cand[j].push_back(0);
                        break;
                    }
                    case 'C': {
                        cand[j].push_back(1);
                        break;
                    }
                    case 'S': {
                        cand[j].push_back(2);
                    }
                }
            for(int u0 = 0; u0 < 3; ++u0)
                for(int u1 = 0; u1 < 3; ++u1) {
                    if(f[pre][u0][u1] == INF)
                        continue;
                    for(int w0: cand[0])
                        for(int w1: cand[1]) {
                            int *vec = tr[u0][u1][w0][w1];
                            if(vec[2] == INF)
                                continue;
                            assert(!vec[2]);
                            f[cur][vec[0]][vec[1]] = min(f[cur][vec[0]][vec[1]], f[pre][u0][u1] + (grid[0][i] == '.' && !w0) + (grid[1][i] == '.' && !w1));
                        }
                }
            // for(int u0 = 0; u0 < 3; ++u0)
            //     for(int u1 = 0; u1 < 3; ++u1)
            //         if(f[cur][u0][u1] < INF)
            //             printf("%d %d %d: %d\n", i, u0, u1, f[cur][u0][u1]);
        }
        int ans = INF;
        for(int u0 = 0; u0 < 3; ++u0)
            for(int u1 = 0; u1 < 3; ++u1)
                ans = min(ans, f[cur][u0][u1]);
        return ans;
    }
public:
    int guardCastle(vector<string>& grid) {
        int n = grid[0].size(), s = -1;
        for(int i = 0; i < 2; ++i)
            for(int j = 0; j < n; ++j)
                if(grid[i][j] == 'C') {
                    s = i * n + j;
                } else if(grid[i][j] == 'P') {
                    grid[i][j] = 'C';
                }
        int ans = calc(grid);
        for(int i = 0; i < 2; ++i)
            for(int j = 0; j < n; ++j)
                if(grid[i][j] == 'C' && i * n + j != s)
                    grid[i][j] = 'S';
        ans = min(ans, calc(grid));
        return ans <= n * 2 ? ans : -1;
    }
};
