#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1;
int n, m, seg[maxn << 1 | 1];
LL a[maxn], b[maxn];
LL read() {
	LL ret = 0;
	static char buf[11];
	scanf("%s", buf);
	for(char *ptr = buf; *ptr; ++ptr)
		ret = ret << 5 | (*ptr - 'a' + 1);
	return ret;
}
inline int seg_idx(int L, int R) {
	return (L + R) | (L < R);
}
void seg_upd(int L, int R, int x, int v) {
	if(L == R) {
		seg[seg_idx(L, R)] += v;
		return;
	}
	int M = (L + R) >> 1;
	if(x <= M)
		seg_upd(L, M, x, v);
	else
		seg_upd(M + 1, R, x, v);
	seg[seg_idx(L, R)] = min(seg[seg_idx(L, M)], seg[seg_idx(M + 1, R)]);
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
		a[i] = read();
	for(int i = 1; i <= m; ++i)
		b[i] = read();
	sort(b + 1, b + m + 1);
	m = unique(b + 1, b + m + 1) - b - 1;
	LL ans = 0;
	for(int i = 1, j = 1; i <= n; ++i) {
		for( ; j <= n && seg[seg_idx(1, m)] < 1; ++j) {
			int k = lower_bound(b + 1, b + m + 1, a[j]) - b;
			a[j] = b[k] == a[j] ? k : 0;
			if(a[j])
				seg_upd(1, m, a[j], 1);
		}
		if(seg[seg_idx(1, m)] >= 1)
			ans += n + 2 - j;
		if(a[i])
			seg_upd(1, m, a[i], -1);
	}
	printf("%lld\n", ans);
	return 0;
}
