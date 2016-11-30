#include <vector>
#include <stdio.h>
const int maxn = 50001, maxd = 16;
int n, m, a[maxn], f[maxn][2], dep[maxn], fa[maxd][maxn];
std::vector<int> e[maxn];
void dfs(int u)
{
	f[u][0] ^= a[u];
	for(std::vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
	{
		int v = *it;
		if(v == fa[0][u])
			continue;
		dep[v] = dep[u] + 1;
		fa[0][v] = u;
		dfs(v);
		f[u][0] ^= f[v][1];
		f[u][1] ^= f[v][0];
	}
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for(int i = 1; i < n; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1);
	for(int d = 1; 1 << d <= n; ++d)
		for(int i = 1; i <= n; ++i)
			fa[d][i] = fa[d - 1][fa[d - 1][i]];
	scanf("%d", &m);
	while(m--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		int pv = v;
		for(int i = dep[v] - dep[u], d = 0; i > 0; i >>= 1, ++d)
			if(i & 1)
				pv = fa[d][pv];
		if(u == pv)
		{
			puts("INVALID");
			continue;
		}
		int SG = f[1][1] ^ ((dep[u] & 1) == (dep[v] & 1) ? (f[u][0] ^ f[u][1]) : 0);
		puts(SG ? "YES" : "NO");
	}
	return 0;
}
