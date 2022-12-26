#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef __int128_t i128;
const int maxn = (int)1e6 + 1;

void solve() {
	int n, dt, L = 0, R = 0;
	static int que[maxn];
	static LL a[maxn], s[maxn], f[maxn];
	scanf("%d%d", &n, &dt);
	a[0] = s[0] = f[0] = 0;
	que[R++] = 0;
	for(int i = 1; i <= n; ++i) {
		scanf("%lld", a + i);
		s[i] = s[i - 1] + a[i];
		auto calc = [&](int j) {
			return f[j] + (i - j) * a[i] - (s[i] - s[j]) + dt;
		};
		auto cmp = [&](int u, int v, int w) {
			LL uF = s[u] + f[u], vF = s[v] + f[v], wF = s[w] + f[w];
			return (v - u) * (i128)(wF - uF) - (w - u) * (i128)(vF - uF);
		};
		LL &cur = f[i] = calc(que[L]), nxt;
		for( ; L + 1 < R && cur >= (nxt = calc(que[L + 1])); cur = nxt, ++L);
		for( ; L + 1 < R && cmp(que[R - 2], que[R - 1], i) <= 0; --R);
		que[R++] = i;
	}
	printf("%lld\n", f[n]);
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
