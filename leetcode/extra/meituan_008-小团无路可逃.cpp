#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = (int)1e5 + 1;

int main() {
    int n, x, y;
    static int disX[maxn], disY[maxn];
    static vector<int> e[maxn];
    scanf("%d%d%d", &n, &x, &y);
    for(int i = 1; i < n; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    auto bfs = [&](int s, int dis[]) {
        memset(dis + 1, -1, n * sizeof(int));
        queue<int> que;
        dis[s] = 0;
        que.push(s);
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            for(int v: e[u])
                if(dis[v] == -1) {
                    dis[v] = dis[u] + 1;
                    que.push(v);
                }
        }
    };
    bfs(x, disX);
    bfs(y, disY);
    int ans = 0;
    for(int i = 1; i <= n; ++i)
        if(disX[i] > disY[i])
            ans = max(ans, disX[i]);
    printf("%d\n", ans);
    return 0;
}
