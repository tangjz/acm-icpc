#include <stdio.h>
typedef long long LL;
const int maxn = 100001;
int n, m, a[maxn], b[maxn], sz, stk[maxn], f[maxn], rem;
LL ans;
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		scanf("%d%d", a + i, b + i);
	stk[sz++] = n;
	for(int i = n - 1; i >= 0; --i) {
		for( ; sz && b[stk[sz - 1]] >= b[i]; --sz);
		f[i] = stk[sz - 1];
		stk[sz++] = i;
	}
	for(int i = 0, j = 0, rem = a[0], c = 0; i < n; c -= a[i++]) {
		if(c < 0) {
			puts("-1");
			return 0;
		}
		int cnt = 0, lim = m - c;
		for( ; j < f[i] && cnt < lim; ++j) {
			int tmp = rem < lim - cnt ? rem : lim - cnt;
			cnt += tmp;
			if((rem -= tmp) > 0)
				break;
			rem = a[j + 1];
		}
		c += cnt;
		ans += (LL)cnt * b[i];
	}
	printf("%lld\n", ans);
	return 0;
}
