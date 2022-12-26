#include <bits/stdc++.h>
const int maxn = (int)1e5 + 1, BLEN = 16, BMSK = (1 << BLEN) - 1;
char op[3];
int n, m, dt, x, a[BLEN + 1][maxn];
long long ans;
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i) {
		scanf("%d", &x);
		for(int j = 0, msk = 1; j <= BLEN; msk |= 1 << (++j))
			a[j][i] = x & msk;
	}
	for(int i = 0; i < BLEN; ++i)
		std::sort(a[i], a[i] + n);
	while(m--) {
		scanf("%s%d", op, &x);
		if(op[0] == 'A') {
			dt = (dt + x) & BMSK;
		} else {
			int *arr = a[x], msk = (1 << (x + 1)) - 1;
			int L = ((1 << x) - dt) & msk, R = (msk - dt) & msk;
			int cnt = std::lower_bound(arr, arr + n, R + 1) - std::lower_bound(arr, arr + n, L);
			ans += L > R ? n + cnt : cnt;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
