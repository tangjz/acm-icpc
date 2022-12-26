#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ULL;
const int maxn = (int)1e3 + 1, mod = 998244353;
int n, lim[5], bin[maxn][maxn], ans;
ULL f[5][maxn];
inline void mod_inc(int &x, int y) {
	(x += y) >= mod && (x -= mod);
}
inline void mod_fix(ULL &x) {
	x >= mod && (x %= mod);
}
inline void mod_inc(ULL &x, ULL y) {
	x + y < x && (x %= mod);
	x += y;
}
int main() {
	scanf("%d", &n);
	lim[0] = n >> 2;
	for(int i = 1; i < 5; ++i) {
		scanf("%d", lim + i);
		lim[0] = min(lim[0], lim[i]);
	}
	for(int i = 0; i <= n; ++i) {
		bin[i][0] = bin[i][i] = 1;
		for(int j = 1; j < i; ++j)
			mod_inc(bin[i][j] = bin[i - 1][j], bin[i - 1][j - 1]);
	}
	for(int i = 0; i <= lim[0]; ++i) {
		int upp = n - (i << 2), cur = 0, nxt;
		f[0][0] = bin[upp + i][i];
		if(i & 1)
			f[0][0] = mod - f[0][0];
		for(int j = 1; j < 5; ++j) {
			nxt = min(cur + lim[j] - i, upp);
			memset(f[j], 0, (nxt + 1) * sizeof(ULL));
			for(int x = 0; x <= cur; ++x) {
				mod_fix(f[j - 1][x]);
				if(!f[j - 1][x])
					continue;
				for(int y = i, z = x; y <= lim[j] && z <= nxt; ++y, ++z)
					mod_inc(f[j][z], f[j - 1][x] * bin[z][x]);
			}
			cur = nxt;
		}
		mod_fix(f[4][upp]);
		mod_inc(ans, (int)f[4][upp]);
	}
	printf("%d\n", ans);
	return 0;
}
