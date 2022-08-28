#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)1e3 + 1;

int main() {
    int n;
    static int dis[maxn][maxn];
    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            scanf("%d", dis[i] + j);
    int u, v, lim;
    scanf("%d%d%d", &u, &v, &lim);
    int L = -1, R = lim - 1;
    while(L < R) {
        int M = (L + R + 1) >> 1;
        int upp = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                upp = max(upp, min(dis[i][j], M + min(dis[u][i] + dis[v][j], dis[v][i] + dis[u][j])));
        if(upp + M < lim) {
            L = M;
        } else {
            R = M - 1;
        }
    }
    printf("%d\n", L);
    return 0;
}
