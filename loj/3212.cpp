#include <bits/stdc++.h>
typedef long long LL;
const int maxn = (int)4e7 + 1, maxm = (int)1e5 + 1, BLEN = 18, BMSK = (1 << 30) - 1;
const LL BASE = (LL)1e18;
int n, t, f[maxn], que[maxn], L, R;
LL s[maxn];
int main() {
	freopen("partition.in", "r", stdin);
	freopen("partition.out", "w", stdout);
	scanf("%d%d", &n, &t);
	if(!t) {
		for(int i = 1; i <= n; ++i)
			scanf("%lld", s + i);
	} else {
		static int x, y, z, m;
		scanf("%d%d%d%lld%lld%d", &x, &y, &z, s + 1, s + 2, &m);
		for(int i = 3; i <= n; ++i)
			s[i] = (x * (int)s[i - 1] + y * (int)s[i - 2] + z) & BMSK;
		int pos = 1;
		while(m--) {
			int upp, x, y;
			scanf("%d%d%d", &upp, &x, &y);
			y -= x - 1;
			for( ; pos <= upp; ++pos)
				s[pos] = (int)s[pos] % y + x;
		}
	}
	que[R++] = 0;
	for(int i = 1; i <= n; ++i) {
		s[i] += s[i - 1];
		for( ; L + 1 < R && s[i] - s[que[L + 1]] >= s[que[L + 1]] - s[f[que[L + 1]]]; ++L);
		f[i] = que[L];
		for( ; L < R && s[i] + (s[i] - s[f[i]]) <= s[que[R - 1]] + (s[que[R - 1]] - s[f[que[R - 1]]]); --R);
		que[R++] = i;
	}
	__int128_t ans = 0, tmp;
	for(int i = n; i > 0; i = f[i]) {
		tmp = s[i] - s[f[i]];
		ans += tmp * tmp;
	}
	if(ans < BASE) {
		printf("%lld\n", (LL)ans);
	} else {
		printf("%lld%0*lld\n", (LL)(ans / BASE), BLEN, (LL)(ans % BASE));
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
