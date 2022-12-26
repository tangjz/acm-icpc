#include <stdio.h>
const int maxn = 21, maxd = 1 << 20 | 1, mod = 998244353;
int n, m, e[maxn], bits[maxd], f[maxd];
int main() {
	scanf("%d%d", &n, &m);
	while(m--) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[--u] |= 1 << (--v);
	}
	f[0] = 1;
	for(int i = 1; i < 1 << n; ++i) {
		bits[i] = bits[i >> 1] + (i & 1);
		for(int msk = i & e[bits[i] - 1], lbt; msk; msk ^= lbt) {
			lbt = msk & -msk;
			(f[i] += f[i ^ lbt]) >= mod && (f[i] -= mod);
		}
	}
	printf("%d\n", f[(1 << n) - 1]);
	return 0;
}
