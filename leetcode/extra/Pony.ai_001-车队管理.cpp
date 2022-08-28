#include <bits/stdc++.h>
using namespace std;

const int maxn = 201, OFS = 100, maxv = 8;

int main() {
    int n, m;
    static int cnt[maxn][maxn] = {};
    scanf("%d%d", &n, &m);
    int xL = OFS, xR = OFS, yL = OFS, yR = OFS;
    cnt[OFS][OFS] = n;
    for(bool upd = 1; upd; ) {
        upd = 0;
        for(int x = xL; x <= xR; ++x)
            for(int y = yL; y <= yR; ++y) {
                if(cnt[x][y] < maxv)
                    continue;
                upd = 1;
                int d = cnt[x][y] >> 3;
                cnt[x][y] &= 7;
                for(int dx = -1; dx <= 1; ++dx)
                    for(int dy = -1; dy <= 1; ++dy) {
                        if(!dx && !dy)
                            continue;
                        cnt[x + dx][y + dy] += d;
                    }
            }
        bool toL = 0, toR = 0, toU = 0, toD = 0;
        for(int x = xL - 1; x <= xR + 1; ++x) {
            toL |= cnt[x][yL - 1] >= maxv;
            toR |= cnt[x][yR + 1] >= maxv;
        }
        for(int y = yL - 1; y <= yR + 1; ++y) {
            toU |= cnt[xL - 1][y] >= maxv;
            toD |= cnt[xR + 1][y] >= maxv;
        }
        xL -= toU;
        xR += toD;
        yL -= toL;
        yR += toR;
    }
    for(int i = 0; i < OFS + OFS; ++i)
        for(int j = 1; j < OFS + OFS; ++j)
            cnt[i][j] += cnt[i][j - 1];
    for(int i = 1; i < OFS + OFS; ++i)
        for(int j = 0; j < OFS + OFS; ++j)
            cnt[i][j] += cnt[i - 1][j];
    while(m--) {
        scanf("%d%d%d%d", &xL, &yL, &xR, &yR);
        xL = max(xL, -OFS + 1) + OFS;
        xR = min(xR, OFS - 1) + OFS;
        yL = max(yL, -OFS + 1) + OFS;
        yR = min(yR, OFS - 1) + OFS;
        printf("%d\n", xL > xR || yL > yR ? 0 : cnt[xR][yR] - cnt[xL - 1][yR] - cnt[xR][yL - 1] + cnt[xL - 1][yL - 1]);
    }
    return 0;
}
