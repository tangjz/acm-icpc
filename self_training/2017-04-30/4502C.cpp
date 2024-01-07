#include <cstdio>
typedef long long LL;
const int maxn = 51;
int n, a[maxn], e[maxn][maxn], ans1;
LL ans2;
void dfs(int u, int dep)
{
	ans1 += a[u];
	ans2 += (LL)a[u] << dep;
	for(int i = 1; i <= e[u][0]; ++i)
		dfs(e[u][i], dep + 1);
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for(int i = 1; i <= n; ++i)
		for(int j = 0; j <= e[i][0]; ++j)
			scanf("%d", e[i] + j);
	dfs(1, 0);
	printf("%d %lld\n", ans1, ans2);
	return 0;
}
