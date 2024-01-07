#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 3, maxc = 26;
int len, a[maxc], b[maxc], h[maxn << 1 | 1];
LL f[maxn], g[maxn], pre[maxn], suf[maxn];
char buf[maxn], str[maxn << 1 | 1];
int main() {
	scanf("%s", buf + 1);
	len = strlen(buf + 1);
	for(int i = 0; i < maxc; ++i)
		scanf("%d%d", a + i, b + i);
	str[0] = '$';
	for(int i = 1; i <= len; ++i) {
		int o = buf[i] - 'a';
		f[i] = f[i - 1] + a[o];
		g[i] = g[i - 1] + b[o];
		str[i * 2 - 1] = buf[i];
		str[i * 2] = '#';
	}
	LL mx = 0;
	for(int i = 1; i <= len; ++i) {
		mx = min(mx, f[i] - g[i]);
		pre[i] = g[i] + mx;
	}
	mx = g[len] - f[len];
	for(int i = len; i >= 1; --i) {
		mx = min(mx, g[i - 1] - f[i - 1]);
		suf[i] = f[len] - g[i - 1] + mx;
	}
	LL ans = ~0ull >> 1;
	for(int i = 1, mx = 0, id; i < len * 2; ++i) {
		h[i] = i < mx ? min(h[id * 2 - i], mx - i) : 1;
		for( ; str[i - h[i]] == str[i + h[i]]; ++h[i]);
		if(mx < i + h[i]) {
			mx = i + h[i];
			id = i;
		}
		int L = (i - h[i] + 1) / 2 + 1, R = (i + h[i]) / 2;
		if(L <= R) {
			ans = min(ans, f[L - 1] + suf[R + 1]);
			ans = min(ans, f[len] - f[R] + pre[L - 1]);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
