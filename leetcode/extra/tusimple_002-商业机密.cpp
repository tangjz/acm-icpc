#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)1e5 + 1;

int main() {
    int n, m, q, d, tot = 0;
    static int que[maxn], dis[maxn];
    static vector<int> e[maxn];
    scanf("%d%d%d%d", &n, &m, &q, &d);
    memset(dis + 1, -1, n * sizeof(int));
    for(int i = 1; i <= n; ++i)
        e[i].clear();
    while(q--) {
        int u;
        scanf("%d", &u);
        if(dis[u] == -1) {
            dis[u] = 0;
            que[tot++] = u;
        }
    }
    while(m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for(int i = 0; i < tot; ++i) {
        int u = que[i];
        for(int v: e[u])
            if(dis[v] == -1) {
                dis[v] = dis[u] + 1;
                que[tot++] = v;
            }
    }
    for(int i = 1; i <= n; ++i) {
        int dist = 0, cnt = 0;
        for( ; dist < dis[i]; ++cnt, dist += cnt * d);
        printf("%d%c", cnt, " \n"[i == n]);
    }
    return 0;
}
