#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = (int)1e3 + 1, maxl = 21;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;

int main() {
    int n, m, tot = 0;
    static vector<pair<int, int> > e[maxn];
    unordered_map<string, int> idx;
    scanf("%d%d", &n, &m);
    auto getID = [&]() {
        static char buf[maxl];
        scanf("%s", buf);
        int id = idx.insert({(string)buf, idx.size()}).first -> second;
        if(id == tot) {
            e[tot].clear();
            ++tot;
        }
        return id;
    };
    while(m--) {
        int u = getID(), v = getID(), w;
        scanf("%d", &w);
        e[u].push_back({v, w});
    }
    m = tot;
    int q;
    scanf("%d", &q);
    while(q--) {
        int s = getID(), t = getID();
        if(s >= m || t >= m) {
            puts("INF");
            continue;
        }
        priority_queue<pair<LL, int> > que;
        static LL dis[maxn];
        static bool vis[maxn];
        memset(dis, 0x3f, n * sizeof(LL));
        memset(vis, 0, n * sizeof(bool));
        dis[s] = 0;
        que.push({0, s});
        while(!que.empty()) {
            int u = que.top().second;
            que.pop();
            if(vis[u])
                continue;
            vis[u] = 1;
            if(u == t)
                break;
            for(auto &it: e[u]) {
                int v = it.first;
                LL tmp = dis[u] + it.second;
                if(dis[v] > tmp) {
                    dis[v] = tmp;
                    que.push({-dis[v], v});
                }
            }
        }
        if(dis[t] == INF) {
            puts("INF");
        } else {
            printf("%lld\n", dis[t]);
        }
    }
    return 0;
}
