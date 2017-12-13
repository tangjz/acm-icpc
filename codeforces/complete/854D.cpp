#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long double DB;
const int maxn = (int)1e5 + 9, maxm = (int)1e6 + 9, INF = 0x3f3f3f3f;
const LL INF2 = 0x3f3f3f3f3f3f3f3fLL;
int n, m, dt, w[maxn];
LL f[maxm], g[maxm];
struct Node {
	int d, f, t, c;
	void read() {
		scanf("%d%d%d%d", &d, &f, &t, &c);
	}
	bool operator < (Node const &x) const {
		return d < x.d;
	}
} a[maxn];
int main() {
	int mx = 0;
	scanf("%d%d%d", &n, &m, &dt);
	++dt;
	for(int i = 1; i <= m; ++i) {
		a[i].read();
		mx = max(mx, a[i].d);
	}
	++mx;
	sort(a + 1, a + m + 1);
	{ // arrival
		int rem = n;
		LL cnt = 0;
		memset(w + 1, 0x3f, n * sizeof(int));
		memset(f + 1, 0x3f, mx * sizeof(LL));
		for(int i = 1; i <= m; ++i) {
			if(a[i].t)
				continue;
			if(a[i].c < w[a[i].f]) {
				if(w[a[i].f] == INF) {
					--rem;
					w[a[i].f] = 0;
				}
				cnt += a[i].c - w[a[i].f];
				w[a[i].f] = a[i].c;
				if(!rem)
					f[a[i].d] = min(f[a[i].d], cnt);
			}
		}
		for(int i = 2; i <= mx; ++i)
			f[i] = min(f[i], f[i - 1]);
	}
	{ // departure
		int rem = n;
		LL cnt = 0;
		memset(w + 1, 0x3f, n * sizeof(int));
		memset(g + 1, 0x3f, mx * sizeof(LL));
		for(int i = m; i >= 1; --i) {
			if(a[i].f)
				continue;
			if(a[i].c < w[a[i].t]) {
				if(w[a[i].t] == INF) {
					--rem;
					w[a[i].t] = 0;
				}
				cnt += a[i].c - w[a[i].t];
				w[a[i].t] = a[i].c;
				if(!rem)
					g[a[i].d] = min(g[a[i].d], cnt);
			}
		}
		for(int i = mx - 1; i >= 1; --i)
			g[i] = min(g[i], g[i + 1]);
	}
	LL ans = INF2;
	for(int i = 1; i + dt <= mx; ++i)
		ans = min(ans, f[i] + g[i + dt]);
	if(ans < INF2)
		printf("%I64d\n", ans);
	else
		puts("-1");
	return 0;
}
