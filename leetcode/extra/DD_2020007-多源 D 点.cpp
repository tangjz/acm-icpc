#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1;
int n, lim, tot, ord[maxn], par[maxn];
pair<int, int> f[2][maxn];
vector<int> e[maxn];
bool sp[maxn];
int main() {
    int m;
    assert(scanf("%d%d%d", &n, &m, &lim) == 3);
    assert(1 <= min(n, min(m, lim)) && max(n, max(m, lim)) <= 100000);
    while(m--) {
        int x;
        assert(scanf("%d", &x) == 1);
        assert(1 <= x && x <= n);
        sp[x] = 1;
    }
    for(int i = 2, x; i <= n; ++i) {
        assert(scanf("%d", &x) == 1);
        assert(1 <= x && x <= n);
        e[i].push_back(x);
        e[x].push_back(i);
    }
	tot = 0;
    par[1] = -1;
	ord[tot++] = 1;
	for(int i = 0; i < tot; ++i) {
		int u = ord[i];
		for(int v: e[u])
			if(v != par[u]) {
				par[v] = u;
				ord[tot++] = v;
			}
        f[0][u] = f[1][u] = {-1, -1};
        if(sp[u])
            f[0][u] = {0, u};
	}
    assert(tot == n);
    for(int i = n - 1; i >= 0; --i) {
        int u = ord[i], p = par[u];
        if(p == -1 || f[0][u].first < 0)
            continue;
        pair<int, int> tmp = {f[0][u].first + 1, u};
        if(f[0][p] < tmp)
            swap(f[0][p], tmp);
        if(f[1][p] < tmp)
            swap(f[1][p], tmp);
    }
    int cnt = 0;
    for(int i = 0; i < n; ++i) {
        int u = ord[i], p = par[u];
        if(p == -1)
            continue;
        int o = f[0][p].second == u;
        if(f[o][p].first < 0)
            continue;
        pair<int, int> tmp = {f[o][p].first + 1, p};
        if(f[0][u] < tmp)
            swap(f[0][u], tmp);
        if(f[1][u] < tmp)
            swap(f[1][u], tmp);
    }
    for(int i = 1; i <= n; ++i)
        cnt += f[0][i].first <= lim;
    printf("%d\n", cnt);
	return 0;
}
