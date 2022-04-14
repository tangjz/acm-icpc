#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
    const int maxn = 501, maxd = 4, maxk = 11, maxm = maxn * maxn;
    const int dx[maxd] = {0, 1, 0, -1}, dy[maxd] = {1, 0, -1, 0};
    int n, m, q;
    static int e[maxd][maxn][maxn], dis[maxk][maxn][maxn];
    scanf("%d%d%d", &n, &m, &q);
    for(int d = 0; d < maxd; ++d) {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                e[d][i][j] = 0;
            }
        }
    }
    for(int i = 0; i < n; ++i)
        for(int j = 1; j < m; ++j) {
            int x;
            scanf("%d", &x);
            e[0][i][j - 1] = e[2][i][j] = x;
        }
    for(int i = 1; i < n; ++i)
        for(int j = 0; j < m; ++j) {
            int x;
            scanf("%d", &x);
            e[1][i - 1][j] = e[3][i][j] = x;
        }
    if(q & 1) {
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                printf("-1%c", " \n"[j == m - 1]);
        return;
    }
    q >>= 1;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            dis[0][i][j] = 0;
    for(int i = 1; i <= q; ++i)
        for(int x = 0; x < n; ++x)
            for(int y = 0; y < m; ++y) {
                dis[i][x][y] = INT_MAX;
                for(int d = 0; d < maxd; ++d)
                    if(e[d][x][y])
                        dis[i][x][y] = min(dis[i][x][y], dis[i - 1][x + dx[d]][y + dy[d]] + e[d][x][y]);
            }
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            printf("%d%c", dis[q][i][j] << 1, " \n"[j == m - 1]);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
        solve();
		// printf("%lld\n", solve());
	}
	return 0;
}