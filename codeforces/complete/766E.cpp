#include <cstdio>
#include <vector>
const int maxn = 100001, maxd = 21;
int n, mx, a[maxn], sz[maxn], cnt[maxn][maxd];
std::vector<int> e[maxn];
long long ans;
void dfs(int u, int fa)
{
	ans += a[u];
	for(int i = 0; i < mx; ++i)
		if(a[u] & (1 << i))
			++cnt[u][i];
	++sz[u];
	for(std::vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
	{
		int v = *it;
		if(v == fa)
			continue;
		dfs(v, u);
		for(int i = 0; i < mx; ++i)
		{
			int aL = cnt[u][i], aR = sz[u] - cnt[u][i];
			int bL = cnt[v][i], bR = sz[v] - cnt[v][i];
			ans += ((long long)aL * bR + (long long)aR * bL) << i;
			if(a[u] & (1 << i))
				cnt[u][i] += bR;
			else
				cnt[u][i] += bL;
		}
		sz[u] += sz[v];
	}
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", a + i);
		for( ; (1 << mx) <= a[i]; ++mx);
	}
	for(int i = 1; i < n; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1, 0);
	printf("%I64d\n", ans);
	return 0;
}
