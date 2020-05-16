#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ULL;
const int maxn = 201, mod = (int)1e9 + 7, maxt = 18;
int n, m, nxt[maxn], f[2][maxn][maxn];
char buf[maxn];
int main() {
	scanf("%d%d%s", &n, &m, buf);
	for(int i = 1, j; i < n; ++i) {
		for(j = nxt[i]; j && buf[j] != buf[i]; j = nxt[j]);
		nxt[i + 1] = j + (buf[i] == buf[j]);
	}
	for(int i = 0; i < n; ++i) {
		++f[0][i << 1][i << 1];
		++f[0][i << 1 | 1][i << 1 | 1];
		int j = i;
		for( ; j && buf[j] != '0'; j = nxt[j]);
		j += buf[j] == '0';
		if(j < n) {
			++f[0][i << 1][j << 1];
			++f[0][i << 1 | 1][j << 1 | 1];
		} else {
			j = nxt[j];
			++f[0][i << 1][j << 1];
			++f[0][i << 1][j << 1 | 1];
			++f[0][i << 1 | 1][j << 1 | 1];
		}
	}
	for(int i = 0; i < n; ++i) {
		++f[1][i << 1][i << 1];
		++f[1][i << 1 | 1][i << 1 | 1];
		int j = i;
		for( ; j && buf[j] != '1'; j = nxt[j]);
		j += buf[j] == '1';
		if(j < n) {
			++f[1][i << 1][j << 1];
			++f[1][i << 1 | 1][j << 1 | 1];
		} else {
			j = nxt[j];
			++f[1][i << 1][j << 1];
			++f[1][i << 1][j << 1 | 1];
			++f[1][i << 1 | 1][j << 1 | 1];
		}
	}
	for(int i = 2; i <= m; ++i) {
		int pre = i & 1, cur = pre ^ 1;
		int (*F1)[maxn] = f[cur], (*F2)[maxn] = f[pre];
		static ULL g[maxn][maxn];
		static int tim[maxn][maxn];
		for(int j = 0; j < n << 1; ++j)
			for(int k = 0; k < n << 1; ++k)
				g[j][k] = tim[j][k] = 0;
		for(int j = 0; j < n << 1; ++j)
			for(int k = 0; k < n << 1; ++k) if(F1[j][k])
				for(int l = 0; l < n << 1; ++l) if(F2[k][l]) {
					g[j][l] += (ULL)F1[j][k] * F2[k][l];
					(++tim[j][l]) == maxt && (g[j][l] %= mod, tim[j][l] = 0);
				}
		for(int j = 0; j < n << 1; ++j)
			for(int k = 0; k < n << 1; ++k)
				F2[j][k] = tim[j][k] ? g[j][k] % mod : g[j][k];
	}
	int ans = 0, (*F)[maxn] = f[m & 1];
	for(int i = 0; i < n; ++i)
		(ans += F[0][i << 1 | 1]) >= mod && (ans -= mod);
	printf("%d\n", ans);
	return 0;
}
