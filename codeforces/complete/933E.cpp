#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)3e5 + 3;
int n, a[maxn], cnt, p[maxn], m, out[maxn];
LL f[maxn];
bool v[maxn];
int descension(int pos) {
	int dt = min(a[pos], a[pos + 1]);
	if(dt)
		out[++m] = pos;
	a[pos] -= dt;
	a[pos + 1] -= dt;
	return dt;
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		LL odd = f[max(i - 2, 0)] + a[i], even = f[max(i - 3, 0)] + max(a[i - 1], a[i]);
		f[i] = min(odd, even);
		v[i] = f[i] != odd;
	}
	// a[n + 1] = 0;
	LL ans = min(f[n - 1], f[n]);
	// printf("%lld\n", ans);
	for(int i = n - (ans == f[n - 1]); i > 0; i -= 2 + v[i])
		p[++cnt] = i;
	reverse(p + 1, p + cnt + 1);
	for(int i = 1; i <= cnt; ++i) {
		int pre = p[i - 1], cur = p[i], ctr = 0;
		if(v[cur])
			ctr += descension(cur - 1);
		ctr += descension(pre + 1);
		ctr += descension(cur);
		assert(ctr == f[cur] - f[pre]);
	}
	printf("%d\n", m);
	for(int i = 1; i <= m; ++i)
		printf("%d\n", out[i]);
	return 0;
}
