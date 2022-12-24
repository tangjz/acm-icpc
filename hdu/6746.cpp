#include <bits/stdc++.h>
using namespace std;
const int maxn = 509, maxv = 9, maxd = 4;
int n, dis[maxn][maxn];
queue<pair<int, int> > que;
inline bool check(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= n;
}
inline void append(int x, int y, int d) {
    if(!check(x, y) || dis[x][y] != -1)
        return;
    dis[x][y] = d;
    que.push(make_pair(x, y));
}
int main() {
    static int low[maxv];
    for(int i = 1; i < maxv; ++i)
        low[i] = i * i << 3;
    int T;
    scanf("%d", &T);
    while(T--) {
        int sx, sy;
        static int a[maxn][maxn];
        scanf("%d%d%d", &n, &sx, &sy);
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j)
                scanf("%d", a[i] + j);

        while(!que.empty())
            que.pop();
        for(int i = 1; i <= n; ++i)
            memset(dis[i] + 1, -1, n * sizeof(int));
        append(sx, sy, 0);
        // for(int dx = -2; dx <= 2; ++dx)
        //     for(int dy = -2; dy <= 2; ++dy)
        //         if(abs(dx) + abs(dy) <= 2)
        //             append(sx + dx, sy + dy, 1);

        int ans = INT_MAX;
        while(!que.empty()) {
            pair<int, int> cur = que.front();
            int x = cur.first, y = cur.second;
            que.pop();

            int tmp = dis[x][y], ctr[maxd + 1] = {};
            for(int dx = -3; dx <= 3; ++dx)
                for(int dy = -3; dy <= 3; ++dy) {
                    int d = abs(dx) + abs(dy);
                    if(d > 3 || !check(x + dx, y + dy))
                        continue;
                    ++ctr[a[x + dx][y + dy]];
                    if(d <= 2)
                        append(x + dx, y + dy, tmp + 1);
                }
            int prd = a[x][y], sum = 0;
            --ctr[prd];
            for(int i = 1, j = maxd - 1; i < maxv; ++tmp) {
                for(sum += prd; i < maxv && sum >= low[i]; ++i) {
                    for( ; j > 0 && !ctr[j]; --j);
                    if(j > 0) {
                        --ctr[j];
                        prd += j;
                    }
                }
            }
            ans = min(ans, tmp);
        }
        printf("%d\n", ans);
    }
    return 0;
}