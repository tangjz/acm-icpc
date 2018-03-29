#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1234569, maxm = 234569, maxd = 187, mod = (int)1e9 + 7;
int tot, pr[maxn], d[maxn], f[maxn], g[maxn], ord[maxn], btot;
bitset<maxd> msk[maxm];
int main() {
	memset(d, -1, sizeof d);
	f[1] = -1;
	g[1] = 1;
	for(int i = 2; i < maxn; ++i) {
		if(d[i] == -1) {
			d[i] = f[i] = tot;
			pr[tot++] = g[i] = i;
		}
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
			d[k] = j;
			f[k] = f[i];
			if(d[i] == j) {
				g[k] = g[i / pr[j]];
				break;
			}
			g[k] = g[i] * pr[j];
		}
	}
	pr[tot] = maxn;
	int L, R;
	while(scanf("%d%d", &L, &R) == 2) {
		int sz = R - L + 1, sqR = 1, ptot = 0;
		for( ; (LL)sqR * sqR <= R; ++sqR);
		for( ; pr[ptot] < sqR; ++ptot);
		printf("length: %d\n", sz);
		printf("prime count (<= sqrt R): %d\n", ptot);
		for(int i = 0; i < sz; ++i)
			ord[i] = L + i;
		sort(ord, ord + sz, [&](int const &u, int const &v) {
			return f[g[u]] < f[g[v]];
		});
		bitset<maxd> fir, tmp;
		btot = 0;
		int adt = 0;
		for(int i = 0, las = -1; i < sz; ++i) {
			int u = ord[i], pid = f[g[u]];
			tmp.reset();
			for( ; u > 1; u /= pr[d[u]])
				if(d[u] < ptot)
					tmp.flip(d[u]);
			if(pid < ptot) {
				msk[btot++] = tmp;
			} else if(las != pid) {
				fir = tmp;
				las = pid;
				++adt;
			} else {
				msk[btot++] = fir ^ tmp;
			}
		}
		printf("matrix: %d %d\n", btot, ptot);
//		for(int i = 0; i < btot; ++i) {
//			for(int j = 0; j < ptot; ++j)
//				putchar('0' + msk[i].test(j));
//			putchar('\n');
//		}
		int rk = 0;
		for(int i = 0; i < ptot; ++i) {
			int k = -1;
			for(int j = rk; j < btot; ++j)
				if(msk[j].test(i)) {
					k = j;
					break;
				}
			if(k == -1)
				continue;
			swap(msk[rk], msk[k]);
			for(int j = rk + 1; j < btot; ++j)
				if(msk[j].test(i))
					msk[j] ^= msk[rk];
			++rk;
		}
		printf("big and rank: %d %d\n", adt, rk);
		int ans = 1;
		for(int i = rk + adt; i < sz; ++i)
			(ans <<= 1) >= mod && (ans -= mod);
		printf("%d\n", ans - 1);
	}
	return 0;
}
