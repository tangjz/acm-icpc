#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 5001;
const LL INF = ~0ULL >> 2;
int n, m, fa[maxn], sz[maxn], c[maxn], d[maxn];
LL f[maxn][maxn], g[maxn][maxn], h[maxn];
void Merge(LL f[], int n, LL g[], int m) {
	static LL tmp[maxn];
	for(int i = 0; i <= n + m; ++i)
		tmp[i] = INF;
	for(int i = 0; i <= n; ++i) if(f[i] < INF)
		for(int j = 0; j <= m; ++j) if(g[j] < INF)
			tmp[i + j] = min(tmp[i + j], f[i] + g[j]);
	for(int i = 0; i <= n + m; ++i)
		f[i] = tmp[i];
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) {
		scanf("%d%d", c + i, d + i);
		if(i > 1)
			scanf("%d", fa + i);
		sz[i] = 1;
		f[i][0] = INF;
		f[i][1] = c[i];
		g[i][0] = 0;
		g[i][1] = c[i];
	}
	f[1][1] -= d[1];
	for(int i = n; i > 1; --i) {
		int p = fa[i];
		for(int j = 0; j <= sz[i]; ++j)
			h[j] = min(f[i][j] < INF ? f[i][j] - d[i] : INF, g[i][j]);
		Merge(f[p], sz[p], h, sz[i]);
		Merge(g[p], sz[p], g[i], sz[i]);
		sz[p] += sz[i];
	}
	int ans = 0;
	for(int i = 1; i <= n; ++i)
		if(min(f[1][i], g[1][i]) <= m)
			ans = i;
	printf("%d\n", ans);
	return 0;
}
