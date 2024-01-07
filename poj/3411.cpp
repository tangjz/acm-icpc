#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 11, maxs = 10 << 10 | 1, INF = 0x3f3f3f3f;

int n, edges[maxn][5], e[maxn][maxn], dis[maxs], ans;
priority_queue<pair<int, int> > pq;

inline void upd(int msk, int d) {
    if(dis[msk] <= d)
        return;
    if((msk >> n) == n - 1)
        ans = min(ans, d);
    dis[msk] = d;
    pq.push(make_pair(-d, msk));
}

void solve() {
    int m;
    scanf("%d%d", &n, &m);
    int all = n << n;
    ans = INF;
    memset(dis, 0x3f, all * sizeof(int));
    for(int i = 0; i < n; ++i)
        e[i][0] = 0;
    for(int i = 0; i < m; ++i) {
        int &a = edges[i][0], &b = edges[i][1], &c = edges[i][2];
        int &p = edges[i][3], &r = edges[i][4];
        scanf("%d%d%d%d%d", &a, &b, &c, &p, &r);
        --a;
        --b;
        --c;
        e[a][++e[a][0]] = i;
    }
    upd(1 << 0, 0);
    while(!pq.empty()) {
        pair<int, int> cur = pq.top();
        pq.pop();
        int u = cur.second;
        if(-cur.first != dis[u])
            continue;
        int a = u >> n;
        for(int t = 1; t <= e[a][0]; ++t) {
            int i = e[a][t], &b = edges[i][1], &c = edges[i][2];
            int &p = edges[i][3], &r = edges[i][4];
            int adt = r;
            if(u & (1 << c))
                adt = min(adt, p);
            upd((u | (1 << b)) ^ ((a ^ b) << n), dis[u] + adt);
        }
    }
    if(ans == INF) {
        puts("impossible");
    } else {
        printf("%d\n", ans);
    }
}

int main() {
    int T = 1;
    // scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        solve();
    }
    return 0;
}
