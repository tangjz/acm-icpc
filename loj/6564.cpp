#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ULL;
const int maxn = (int)7e4 + 1, maxd = maxn, maxs = 1095;
int lcs_fast(int n, int s[], int m, int t[]) {
	if(n < m) {
		swap(n, m);
		swap(s, t);
	}
	int sz = ((n - 1) >> 6) + 1, ans = 0;
	static ULL pos[maxd][maxs] = {}, f[maxs], g[maxs];
	for(int i = 0; i < n; ++i) {
		int o = s[i] - 1;
		pos[o][i >> 6] ^= 1ULL << (i & 63);
	}
	memset(f, 0, sz * sizeof(ULL));
	for(int i = 0; i < m; ++i) {
		int o = t[i] - 1;
		for(int j = 0; j < sz; ++j)
			g[j] = f[j] | pos[o][j];
		for(int j = 0, x = 1, y; j < sz; ++j, x = y) {
			y = (f[j] >> 63) & 1;
			f[j] = f[j] << 1 | x;
		}
		for(int j = 0, x = 0, y; j < sz; ++j, x = y) {
			y = g[j] < f[j] + x;
			f[j] = g[j] - (f[j] + x);
			f[j] = ~f[j] & g[j];
		}
	}
	for(int i = 0; i < n; ++i) {
		int o = s[i] - 1;
		pos[o][i >> 6] ^= 1ULL << (i & 63);
		ans += (f[i >> 6] >> (i & 63)) & 1;
	}
	return ans;
}
int main() {
	int n, m, a[maxn << 1 | 1];
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n + m; ++i)
		scanf("%d", a + i);
	printf("%d\n", lcs_fast(n, a, m, a + n));
	return 0;
}