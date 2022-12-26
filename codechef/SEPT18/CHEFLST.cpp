#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 60, maxd = 10, maxs = 1 << maxd, maxt = 1, mod = (int)1e9 + 7;
int t, n, m, a[maxn + 1][maxn + 1], f[maxn + 1][maxn + 1][maxs + 1], g[maxs + 1], mat[maxn + 1][maxn + 1];
bool chk[maxs + 1];
void FWT(int n, int x[]) { // fwt(x) or ifwt(x) * n
	for(int dt = 1; dt < n; dt <<= 1)
		for(int i = 0; i < n; i += dt << 1)
			for(int j = 0; j < dt; ++j) {
				int tp = x[i + j + dt];
				(x[i + j + dt] = x[i + j] - tp) < 0 && (x[i + j + dt] += mod);
				(x[i + j] += tp) >= mod && (x[i + j] -= mod);
			}
}
inline int mod_inv(int x) {
	return x <= 1 ? x : (mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod));
}
int det(int n, int (*mat)[maxn + 1]) {
	int ret = 1;
	for(int i = 0, j, k; i < n; ++i) {
		k = -1;
		for(j = i; k == -1 && j < n; ++j)
			if(mat[j][i])
				k = j;
		if(k == -1)
			return 0;
		if(i < k) {
			for(j = i; j < n; ++j)
				swap(mat[i][j], mat[k][j]);
			ret && (ret = mod - ret);
		}
		ret = (LL)ret * mat[i][i] % mod;
		int ivs = mod_inv(mat[i][i]);
		for(j = i; j < n; ++j)
			mat[i][j] = (LL)mat[i][j] * ivs % mod;
		for(j = i + 1; j < n; ++j)
			if(mat[j][i]) {
				int d = mod - mat[j][i];
				for(k = i; k < n; ++k)
					mat[j][k] = (mat[j][k] + (LL)mat[i][k] * d) % mod;
			}
	}
	return ret;
}
int main() {
	srand(time(0));
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		m = 1;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j) {
				scanf("%d", a[i] + j);
				for( ; m <= a[i][j]; m <<= 1);
			}
		memset(chk, 0, m * sizeof(bool));
		for(int o = 0; o < maxt; ++o) {
			for(int i = 0; i < n; ++i)
				for(int j = 0; j < n; ++j) {
					memset(f[i][j], 0, m * sizeof(int));
					f[i][j][a[i][j]] = rand() % mod;
					FWT(m, f[i][j]);
				}
			for(int i = 0; i < m; ++i) {
				for(int j = 0; j < n; ++j)
					for(int k = 0; k < n; ++k)
						mat[j][k] = f[j][k][i];
				g[i] = det(n, mat);
			}
			FWT(m, g);
			for(int i = 0; i < m; ++i)
				chk[i] |= g[i];
		}
		for(int i = 0, o = 0; i < m; ++i)
			if(chk[i]) {
				if(o)
					putchar(' ');
				else
					o = 1;
				printf("%d", i);
			}
		putchar('\n');
	}
	return 0;
}
