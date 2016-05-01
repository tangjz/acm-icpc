#pragma comment(linker, "/STACK:10240000,10240000")
#include <cstdio>
#include <vector>
#include <algorithm>
typedef long long LL;
const int maxn = 100001, maxl = 20, mod = 1000000007;
int n, tot, f[maxn], g[1 << maxl], p[1 << maxl], ans;
double h[1 << maxl];
std::vector<int> e[maxn];
void dfs(int u, int fa)
{
	for(std::vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
	{
		int v = *it;
		if(v == fa)
			continue;
		dfs(v, u);
		f[u] |= f[v];
	}
	if(!f[u])
		f[u] = 1 << tot++;
	++g[f[u]];
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i < n; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1, -1);
	std::reverse(g, g + (1 << tot));
	for(int i = 0; i < tot; ++i)
		for(int j = 0; j < 1 << tot; ++j)
			if(j & (1 << i))
				g[j] += g[j ^ (1 << i)];
	std::reverse(g, g + (1 << tot));
	for(int i = 0; i < tot; ++i)
		for(int j = 0; j < 1 << tot; ++j)
			if(j & (1 << i))
				g[j] = g[j ^ (1 << i)] - g[j];
	for(int i = 1; i < 1 << tot; ++i)
	{
		p[i] = -1;
		for(int j = 0; j < tot; ++j)
			if((i & (1 << j)) && (p[i] == -1 || h[i] < h[i ^ (1 << j)]))
			{
				h[i] = h[i ^ (1 << j)];
				p[i] = j;
			}
		h[i] += log(g[i] + 1);
	}
	ans = 1;
	for(int i = (1 << tot) - 1; i; i ^= 1 << p[i])
		ans = ans * (g[i] + 1LL) % mod;
	printf("%d\n", ans);
	return 0;
}
