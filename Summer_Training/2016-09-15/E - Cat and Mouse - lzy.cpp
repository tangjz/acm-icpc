#include <cmath>
#include <cstring>
#include <cstdio>

#include <algorithm>

#define N 400

typedef long long i64;

int n, k, tot;
int x[N + 9], y[N + 9];
i64 s[N + 9][N + 9];
bool g[N + 9][N + 9];
i64 d[N * N + 9];
int mat[N + 9];
bool use[N + 9];

i64 sqr(i64 x) {
	return x * x;
}

bool aug(int u) {
	for (int v = 1; v <= n; ++v)
		if (!use[v] && g[u][v]) {
			use[v] = true;
			if (!mat[v] || aug(mat[v])) return (mat[v] = u);
		}
	return false;
}

int calc(i64 dis) {
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			g[i][j] = s[i][j] > dis;
	memset(mat, 0, sizeof mat);
	int ret = 0;
	for (int i = 1; i <= n; ++i) {
		memset(use, 0, sizeof use);
		ret += aug(i);
	}
	//printf("ret: %d\n", ret);
	return n + n - ret;
}

int gao() {
	int l = 0, r = tot - 1, m;
	std::sort(d, d + tot);
	while (l < r) {
		m = (l + r) >> 1;
		//printf("%d %d %d %lld %d\n", l, r, m, d[m], calc(d[m]));
		if (calc(d[m]) < k) l = m + 1;
		else r = m ;
	}
	return l;
}

int main() {
	while (scanf("%d%d", &n, &k) == 2) {
		for (int i = 1; i <= n + n; ++i)
			scanf("%d%d", x + i, y + i);
		tot = 0;
		for (int i = 1; i <= n; ++i)
			for (int j = n + 1; j <= n + n; ++j)
				d[tot++] = s[i][j - n] = sqr(x[i] - x[j]) + sqr(y[i] - y[j]);
		//printf("%lld\n", d[gao()]);
		printf("%.8f\n", sqrt(d[gao()]));
	}
	return 0;
}
