#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 11;
int n, m;
LL c[maxn][maxn], a[maxn][maxn], b[maxn][maxn], mat[maxn][maxn];
LL det(int n, LL mat[maxn][maxn]) {
	LL ret = 0;
	static int perm[maxn];
	for(int i = 1; i <= n; ++i)
		perm[i] = i;
	do {
		LL ways = 1;
		for(int i = 1; i <= n; ++i) {
			ways *= mat[i][perm[i]];
			for(int j = 1; j < i; ++j)
				if(perm[j] > perm[i])
					ways = -ways;
		}
		ret += ways;
	} while(next_permutation(perm + 1, perm + n + 1));
	return ret;
}
LL choose(int x, int y) {
	return x >= y && y >= 0 ? c[x][y] : 0;
}
LL dfs2(int x, int y) {
	if(x < 1) {
		LL ret = 1;
		for(int i = 1; i <= n + 1; ++i) {
			for(int j = 1; j <= n; ++j)
				for(int k = 1; k <= n; ++k)
					mat[j][k] = choose(a[k][i] - a[j][i - 1] + b[k][i] - b[j][i - 1], a[k][i] - a[j][i - 1] + k - j);
			ret *= det(n, mat);
			for(int j = 1; j <= n; ++j)
				for(int k = 1; k <= n; ++k)
					mat[j][k] = choose(a[i][k] - a[i - 1][j] + b[i - 1][j] - b[i][k], a[i][k] - a[i - 1][j] + k - j);
			ret *= det(n, mat);
		}
		return ret;
	}
	int nx, ny;
	LL low = 0;
	if(y < n) {
		nx = x;
		ny = y + 1;
	} else {
		nx = x - 1;
		ny = 1;
	}
	b[x][y] = 0;
	for(int i = x; i <= n; ++i)
		for(int j = 1; j <= y; ++j)
			low = max(low, b[i][j]);
	LL ret = 0;
	for(int i = low; i <= m; ++i) {
		b[x][y] = i;
		ret += dfs2(nx, ny);
	}
	return ret;
}
LL dfs1(int x, int y) {
	if(x > n)
		return dfs2(n, 1);
	int nx, ny;
	LL low = 0;
	if(y < n) {
		nx = x;
		ny = y + 1;
	} else {
		nx = x + 1;
		ny = 1;
	}
	a[x][y] = 0;
	for(int i = 1; i <= x; ++i)
		for(int j = 1; j <= y; ++j)
			low = max(low, a[i][j]);
	LL ret = 0;
	for(int i = low; i <= m; ++i) {
		a[x][y] = i;
		ret += dfs1(nx, ny);
	}
	return ret;
}
int main() {
	for(int i = 0; i < maxn; ++i) {
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; ++j)
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
	}
	while(scanf("%d%d", &n, &m) == 2) {
		if(n > m)
			swap(n, m);
		for(int i = 1; i <= n; ++i) {
			a[0][i] = a[i][0] = b[i][0] = b[n + 1][i] = 0;
			a[i][n + 1] = a[n + 1][i] = b[0][i] = b[i][n + 1] = m;
		}
		printf("%lld\n", dfs1(1, 1));
	}
	return 0;
}
