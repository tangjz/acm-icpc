#include <bits/stdc++.h>
using namespace std;

const int maxn = 201;
const double INF = 1e20;

void solve() {
    int n, m;
    static int f[maxn], x[maxn], y[maxn];
    static pair<double, int> dis[maxn][maxn];
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; ++i) {
        scanf("%d%d%d", f + i, x + i, y + i);
        for(int j = 0; j < n; ++j)
            dis[i][j] = {INF, j};
        dis[i][i] = {(double)0, i};
    }
    while(m--) {
        int u, v;
        static char typ[11];
        scanf("%d%d%s", &u, &v, typ);
        int df = (f[u] - f[v]) * 5;
        int dx = x[u] - x[v];
        int dy = y[u] - y[v];
        double dist = sqrtl(df * df + dx * dx + dy * dy);
        switch(typ[0]) {
            case 'w': case 's': {
                dis[u][v] = min(dis[u][v], {dist, v});
                dis[v][u] = min(dis[v][u], {dist, u});
                break;
            }
            case 'l': {
                dis[u][v] = min(dis[u][v], {1.0, v});
                dis[v][u] = min(dis[v][u], {1.0, u});
                break;
            }
            case 'e': {
                dis[u][v] = min(dis[u][v], {1.0, v});
                dis[v][u] = min(dis[v][u], {dist * 3, u});
                break;
            }
        }
    }
    for(int k = 0; k < n; ++k)
        for(int i = 0; i < n; ++i) if(i != dis[i][k].second)
            for(int j = 0; j < n; ++j)
                dis[i][j] = min(dis[i][j], {dis[i][k].first + dis[k][j].first, dis[i][k].second});
    scanf("%d", &m);
    while(m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        for( ; u != v; u = dis[u][v].second)
            printf("%d ", u);
        printf("%d\n", v);
    }
}

int main() {
    int T = 1;
    // scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case)
        solve();
    return 0;
}