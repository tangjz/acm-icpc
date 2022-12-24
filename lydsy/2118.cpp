#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 13, maxv = (int)5e5 + 1;
int n, a[maxn], len, seq[maxv], vis[maxv];
LL dis[maxv], L, R, ans;
inline void upd(LL &x, LL y) {
	x > y && (x = y);
}
int main() {
	scanf("%d%lld%lld", &n, &L, &R);
	for(int i = 0; i < n; ++i) {
		scanf("%d", a + i);
		if(a[0] > a[i])
			std::swap(a[0], a[i]);
	}
	memset(dis, 0x3f, a[0] * sizeof(LL));
	dis[0] = 0;
	int com = a[0];
	for(int i = 1; i < n; ++i) {
		com = std::__gcd(com, a[i]);
		int adt = a[i] % a[0];
		for(int j = 0; j < a[0]; j += com) {
			if(vis[j] == i)
				continue;
			int pos = len = 0;
			for(int x = j; vis[x] != i; (x += adt) >= a[0] && (x -= a[0])) {
				vis[x] = i;
				seq[len++] = x;
				if(dis[seq[pos]] > dis[seq[len - 1]])
					pos = len - 1;
			}
			for(int u = pos, v = pos + 1 < len ? pos + 1 : 0; v != pos; u = v, (++v) == len && (v = 0))
				upd(dis[seq[v]], dis[seq[u]] + a[i]);
		}
	}
	for(int i = 0; i < a[0]; ++i)
		if(dis[i] <= R)
			ans += (R - dis[i]) / a[0] - (dis[i] < L ? (L - 1 - dis[i]) / a[0] : -1);
	printf("%lld\n", ans);
	return 0;
}