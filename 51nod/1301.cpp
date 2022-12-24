#include <bits/stdc++.h>
using namespace std;
const int maxn = 1 << 11 | 1, mod = (int)1e9 + 7;
int n, m, f[2][2][maxn];
inline void mod_inc(int &x, int y) {
	(x += y) >= mod && (x -= mod);
}
int main() {
	scanf("%d%d", &n, &m);
	int upp = max(n, m), all, ans = 0;
	for(all = 1; all <= upp; all <<= 1);
	for(int i = 1; i <= m; i <<= 1) {
		int cur = 0, pre = 1;
		memset(f[cur], 0, sizeof f[0]);
		f[cur][0][0] = 1;
		for(int j = 1; j <= upp; ++j) {
			cur ^= 1;
			pre ^= 1;
			memcpy(f[cur], f[pre], sizeof f[0]);
			if(j <= n)
				for(int k = 0; k < all; ++k) {
					mod_inc(f[cur][0][k], f[pre][0][j ^ k]);
					mod_inc(f[cur][1][k], f[pre][1][j ^ k]);
				}
			if(j <= m) {
				int o = !!(i & j);
				for(int k = 0; k < all; ++k) {
					mod_inc(f[cur][0][k], f[pre][o][j ^ k]);
					mod_inc(f[cur][1][k], f[pre][!o][j ^ k]);
				}
			}
		}
		for(int j = i; j < i + i; ++j)
			mod_inc(ans, f[cur][1][j]);
	}
	printf("%d\n", ans);
	return 0;
}
