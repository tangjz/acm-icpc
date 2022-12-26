#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)6e3 + 1, maxm = (int)1e7 + 1;
int t, n, m, a[maxn][maxn];
short v[maxn][maxn];
vector<pair<short, short> > e[maxm];
int main() {
    for(int i = 0, i2 = 0; i2 + i2 < maxm; i2 += (i++) << 1 | 1)
        for(int j = i, j2 = i2; i2 + j2 < maxm; j2 += (j++) << 1 | 1)
            e[i2 + j2].push_back(make_pair((short)i, (short)j));
    scanf("%d", &t);
    for(int Case = 1; Case <= t; ++Case) {
        scanf("%d%d", &n, &m);
        while(n--) {
            int x, y;
            scanf("%d%d", &x, &y);
            v[x][y] = Case;
            scanf("%d", a[x] + y);
        }
        auto get = [&](int x, int y) {
            return v[x][y] == Case ? a[x][y] : 0;
        };
        auto add = [&](int x, int y, int w) {
            v[x][y] == Case && (a[x][y] += w);
        };
        int las = 1;
        printf("Case #%d:\n", Case);
        while(m--) {
            int typ, x, y;
            scanf("%d%d%d", &typ, &x, &y);
            (x += las) >= maxn && (x -= maxn - 1);
            (y += las) >= maxn && (y -= maxn - 1);
            if(typ == 1) {
                v[x][y] = Case;
                scanf("%d", a[x] + y);
            } else if(typ == 2) {
                v[x][y] = 0;
            } else if(typ == 3) {
                int k, w;
                scanf("%d%d", &k, &w);
                for(auto &it : e[k]) {
                    int dx = it.first, dy = it.second;
                    if(x + dx < maxn) {
                        if(y + dy < maxn)
                            add(x + dx, y + dy, w);
                        if(dy && y - dy >= 0)
                            add(x + dx, y - dy, w);
                    }
                    if(dx && x - dx >= 0) {
                        if(y + dy < maxn)
                            add(x - dx, y + dy, w);
                        if(dy && y - dy >= 0)
                            add(x - dx, y - dy, w);
                    }
                    if(dx == dy)
                        continue;
                    swap(dx, dy);
                    if(x + dx < maxn) {
                        if(y + dy < maxn)
                            add(x + dx, y + dy, w);
                        if(dy && y - dy >= 0)
                            add(x + dx, y - dy, w);
                    }
                    if(dx && x - dx >= 0) {
                        if(y + dy < maxn)
                            add(x - dx, y + dy, w);
                        if(dy && y - dy >= 0)
                            add(x - dx, y - dy, w);
                    }
                }
            } else {
                int k;
                long long ans = 0;
                scanf("%d", &k);
                for(auto &it : e[k]) {
                    int dx = it.first, dy = it.second;
                    if(x + dx < maxn) {
                        if(y + dy < maxn)
                            ans += get(x + dx, y + dy);
                        if(dy && y - dy >= 0)
                            ans += get(x + dx, y - dy);
                    }
                    if(dx && x - dx >= 0) {
                        if(y + dy < maxn)
                            ans += get(x - dx, y + dy);
                        if(dy && y - dy >= 0)
                            ans += get(x - dx, y - dy);
                    }
                    if(dx == dy)
                        continue;
                    swap(dx, dy);
                    if(x + dx < maxn) {
                        if(y + dy < maxn)
                            ans += get(x + dx, y + dy);
                        if(dy && y - dy >= 0)
                            ans += get(x + dx, y - dy);
                    }
                    if(dx && x - dx >= 0) {
                        if(y + dy < maxn)
                            ans += get(x - dx, y + dy);
                        if(dy && y - dy >= 0)
                            ans += get(x - dx, y - dy);
                    }
                }
                printf("%lld\n", ans);
                las = (ans + 1) % (maxn - 1);
            }
        }
    }
    return 0;
}
