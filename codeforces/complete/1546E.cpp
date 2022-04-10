#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e3 + 1, mod = 998244353;
void solve() {
    int n;
    static int a[maxn][maxn];
    static bool row[maxn], e[maxn][maxn];
    scanf("%d", &n);
    for(int i = 0; i < n + n; ++i) {
        for(int k = 0; k < n; ++k) {
            scanf("%d", a[i] + k);
            --a[i][k];
        }
        row[i] = 1;
        e[i][i] = 0;
        for(int j = 0; j < i; ++j) {
            bool ban = 0;
            for(int k = 0; !ban && k < n; ++k)
                ban |= a[i][k] == a[j][k];
            e[i][j] = e[j][i] = !ban;
        }
    }
    int cnt = 0;
    static int path[maxn];
    for(int t = 0; t < n; ++t) {
        bool upd = 0;
        for(int k = 0; k < n; ++k) {
            static int v, pos[maxn];
            for(v = 0; v < n; ++v)
                pos[v] = -1;
            for(int i = 0; i < n + n; ++i) {
                if(!row[i])
                    continue;
                int x = a[i][k];
                pos[x] = pos[x] == -1 ? i : -2;
            }
            for(v = 0; v < n && pos[v] < 0; ++v);
            if(v >= n)
                continue;
            upd = 1;
            int x = path[cnt++] = pos[v];
            for(int i = 0; i < n + n; ++i)
                row[i] &= e[x][i];
            // printf("found %d %d: %d\n", x + 1, k + 1, v + 1);
            break;
        }
        if(!upd)
            break;
    }
    int ways = 1;
    // for(int i = 0; i < n + n; ++i) {
    //     if(!row[i])
    //         continue;
    //     for(int j = 0; j < n + n; ++j)
    //         if(row[j])
    //             printf("%d ", (int)e[i][j]);
    //     puts("");
    // }
    for(int i = 0; i < n + n; ++i) {
        if(!row[i])
            continue;
        queue<pair<int, int> > que;
        row[i] = 0;
        // printf("block: ");
        que.push({i, 1});
        while(!que.empty()) {
            int u, tag;
            tie(u, tag) = que.front();
            // printf(" (%d, %d)", u + 1, tag);
            if(tag)
                path[cnt++] = u;
            que.pop();
            for(int v = 0; v < n + n; ++v)
                if(row[v] && !e[u][v]) {
                    row[v] = 0;
                    que.push({v, !tag});
                }
        }
        // puts("");
        (ways <<= 1) %= mod;
    }
    printf("%d\n", ways);
    for(int i = 0; i < cnt; ++i)
        printf("%d%c", path[i] + 1, " \n"[i == cnt - 1]);
}

int main() {
	int T;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
        solve();
	}
	return 0;
}