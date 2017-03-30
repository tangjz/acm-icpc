#include <stdio.h>
#include <cstring>
#include <algorithm>
const int maxn = 100001, maxd = 17;
int t, n, q, f[maxn], dep[maxn], fa[maxd][maxn];
char str[maxn];
int lca(int u, int v)
{
	if(dep[u] > dep[v])
		std::swap(u, v);
	for(int i = dep[v] - dep[u], j = 0; i; i >>= 1, ++j)
		if(i & 1)
			v = fa[j][v];
	if(u == v)
		return u;
	for(int i = maxd - 1; i >= 0; --i)
		if(fa[i][u] != fa[i][v])
		{
			u = fa[i][u];
			v = fa[i][v];
		}
	return fa[0][u];
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%s", str);
		n = strlen(str);
		for(int i = 1, j = 0; i < n; ++i)
		{
			for( ; j && str[i] != str[j]; j = f[j]);
			f[i + 1] = str[i] == str[j] ? ++j : 0;
		}
		dep[0] = 0;
		for(int i = 1; i <= n; ++i)
		{
			dep[i] = dep[f[i]] + 1;
			fa[0][i] = f[i];
		}
		for(int i = 1; i < maxd; ++i)
			for(int j = 1; j <= n; ++j)
				fa[i][j] = fa[i - 1][fa[i - 1][j]];
		scanf("%d", &q);
		printf("Case #%d:\n", Case);
		while(q--)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			printf("%d\n", lca(f[u], f[v]));
		}
	}
	return 0;
}

