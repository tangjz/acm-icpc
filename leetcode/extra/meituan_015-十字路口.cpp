#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = (int)1e4 + 1;

int main() {
    int n, r, c;
    int s, sx, sy;
    int t, tx, ty;
    static int tim[maxn][2];
    scanf("%d%d%d%d%d%d", &r, &c, &sx, &sy, &tx, &ty);
    n = r * c;
    s = (--sx) * c + (--sy);
    t = (--tx) * c + (--ty);
    for(int i = 0; i < n; ++i)
        scanf("%d", tim[i] + 0);
    for(int i = 0; i < n; ++i) {
        scanf("%d", tim[i] + 1);
        tim[i][1] += tim[i][0];
    }
    static int dis[maxn];
    static bool vis[maxn];
    memset(dis, 0x3f, n * sizeof(int));
    memset(vis, 0, n * sizeof(bool));
    priority_queue<pair<int, int> > que;
    auto upd = [&](int u, int dist) {
        if(dis[u] > dist) {
            dis[u] = dist;
            que.push({-dis[u], u});
        }
    };
    upd(s, 0);
    while(!que.empty()) {
        int u = que.top().second;
        que.pop();
        if(vis[u])
            continue;
        vis[u] = 1;
        int ux = u / c, uy = u % c;
        {
            int tmp = dis[u];
            if(tmp % tim[u][1] >= tim[u][0])
                tmp += tim[u][1] - tmp % tim[u][1];
            ++tmp;
            if(ux > 0)
                upd(u - c, tmp);
            if(ux + 1 < r)
                upd(u + c, tmp);
        }
        {
            int tmp = dis[u];
            if(tmp % tim[u][1] < tim[u][0])
                tmp += tim[u][0] - tmp % tim[u][1];
            ++tmp;
            if(uy > 0)
                upd(u - 1, tmp);
            if(uy + 1 < c)
                upd(u + 1, tmp);
        }
    }
    printf("%d\n", dis[t]);
    return 0;
}
