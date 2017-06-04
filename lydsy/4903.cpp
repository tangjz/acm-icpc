#include <cstdio>
const int maxn = 211985, maxs = 1 << 9 | 1, mod = 1000000007;
int n, m, a[maxn], s[maxs][maxs], ans;
inline void mod_inc(int &x, int y) {
	(x += y) >= mod && (x -= mod);
}
int main() {
	scanf("%d", &n);
	for(int i = n - 1; i >= 0; --i) {
		scanf("%d", a + i);
		for( ; 1 << m <= a[i]; ++m);
	}
	int d1 = m >> 1, d2 = m - d1, all = (1 << d2) - 1;
	for(int i = 0; i <= all; ++i)
		++s[0][i];
	ans = mod - n;
	for(int i = 0; i < n; ++i) {
		int x = a[i] >> d2, y = a[i] & all, z = all - y, val = 0;
		for(int j = x; j; j = (j - 1) & x)
			mod_inc(val, s[j][y]);
		mod_inc(val, s[0][y]);
		mod_inc(ans, val);
		for(int j = z; j; j = (j - 1) & z)
			mod_inc(s[x][j | y], val);
		mod_inc(s[x][y], val);
	}
	printf("%d\n", ans);
	return 0;
}
