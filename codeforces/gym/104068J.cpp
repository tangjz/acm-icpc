#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = (int)4e2 + 1;

void solve() {
	int n;
	static int a[4][maxn], w[maxn][maxn], p[maxn], pre[maxn];
	static LL f[2][maxn], dt[maxn];
	static bool vis[maxn];
	scanf("%d", &n);
	for(int i = 0; i < 4; ++i)
		for(int j = 1; j <= n; ++j)
			scanf("%d", a[i] + j);
	for(int i = 1; i <= n; ++i) {
		f[0][i] = LLONG_MIN;
		f[1][i] = p[i] = 0;
		for(int j = 1; j <= n; ++j) {
			w[i][j] = -max(a[3][j] - a[0][i], 0) - max(a[1][i] - a[2][j], 0);
			f[0][i] = max(f[0][i], (LL)w[i][j]);
		}
	}
	for(int rt = 1; rt <= n; ++rt) {
		int las = 0, nxt;
		memset(vis, 0, (n + 1) * sizeof(bool));
		memset(dt, 0x3f, (n + 1) * sizeof(LL));
		p[las] = rt;
		do {
			vis[las] = 1;
			int u = p[las];
			LL low = LLONG_MAX, dif;
			for(int v = 1; v <= n; ++v) {
				if(vis[v])
					continue;
				dif = f[0][u] + f[1][v] - w[u][v];
				if(dif < dt[v]) {
					dt[v] = dif;
					pre[v] = las;
				}
				if(dt[v] < low) {
					low = dt[v];
					nxt = v;
				}
			}
			for(int v = 0; v <= n; ++v)
				if(vis[v]) {
					f[0][p[v]] -= low;
					f[1][v] += low;
				} else {
					dt[v] -= low;
				}
			las = nxt;
		} while(p[las]);
		for(int u = las; u; u = pre[u])
			p[u] = p[pre[u]];
	}
	LL ans = 0;
	for(int i = 1; i <= n; ++i)
		ans += f[0][i] + f[1][i];
	printf("%lld\n", -ans);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}
