#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

const int maxn = 61, maxl = 51;

void solve() {
    int n, m;
    unordered_map<string, int> Hash;
    static char buf[maxl], buf2[maxl];
    static int x[3][maxn];
    static double dis[maxn][maxn];
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        scanf("%s", buf);
        Hash[buf] = i;
        for(int j = 0; j < 3; ++j)
            scanf("%d", x[j] + i);
        dis[i][i] = 0;
        for(int j = 0; j < i; ++j) {
            i64 dis2 = 0;
            for(int k = 0; k < 3; ++k)
                dis2 += (i64)(x[k][i] - x[k][j]) * (x[k][i] - x[k][j]);
            dis[i][j] = dis[j][i] = sqrtl(dis2);
        }
    }
    scanf("%d", &m);
    while(m--) {
        scanf("%s", buf);
        int u = Hash[buf];
        scanf("%s", buf);
        int v = Hash[buf];
        dis[u][v] = 0;
    }
    for(int k = 0; k < n; ++k)
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    scanf("%d", &m);
    while(m--) {
        scanf("%s", buf);
        int u = Hash[buf];
        scanf("%s", buf2);
        int v = Hash[buf2];
        int w = round(dis[u][v]);
        printf("The distance from %s to %s is %d parsecs.\n", buf, buf2, w);
    }
}

int main() {
    int T = 1;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        printf("Case %d:\n", Case);
        solve();
    }
    return 0;
}
