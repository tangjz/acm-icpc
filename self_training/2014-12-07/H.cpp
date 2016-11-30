#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const double eps = 1e-5;
const int maxn = (int)1e6;
int n, q, f[maxn], g[maxn], ff[maxn], pos[maxn], maxl;
long long sg[maxn], ans;
bool vis[maxn];
vector<int> e[maxn];
void dfs1(int u)
{
	vis[u] = 1;
	for(int i = 0, j = (int)e[u].size(); i < j; ++i)
	{
		int &v = e[u][i];
		if(vis[v])
			continue;
		dfs1(v);
		if(f[u] < f[v] + 1)
		{
			pos[u] = v;
			ff[u] = f[u];
			f[u] = f[v] + 1;
		}
		else if(ff[u] < f[v] + 1)
			ff[u] = f[v] + 1;
	}
}
void dfs2(int u)
{
	vis[u] = 1;
	for(int i = 0, j = (int)e[u].size(); i < j; ++i)
	{
		int &v = e[u][i];
		if(vis[v])
			continue;
		int &w = pos[u] == v ? ff[u] : f[u];
		if(f[v] < w + 1)
		{
			pos[v] = u;
			ff[v] = f[v];
			f[v] = w + 1;
		}
		else if(ff[v] < w + 1)
			ff[v] = w + 1;
		dfs2(v);
	}
}
int dp()
{
	for(int i = 1; i <= n; ++i)
		e[i].clear();
	for(int i = 1; i < n; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	memset(f, 0, sizeof f);
	memset(ff, 0, sizeof ff);
	memset(pos, 0, sizeof pos);
	memset(vis, 0, sizeof vis);
	dfs1(1);
	memset(vis, 0, sizeof vis);
	dfs2(1);
	sort(f + 1, f + n + 1);
	return f[n];
}
int main()
{
	while(scanf("%d%d", &n, &q) == 2)
	{
		ans = 0;
		memset(sg, 0, sizeof sg);
		maxl = dp();
		swap(n, q);
		memcpy(g, f, sizeof f);
		maxl = max(maxl, dp());
		for(int i = q; i; --i)
			sg[i] = sg[i + 1] + g[i];
		for(int i = 1, j = q; i <= n; ++i)
		{
			while(j && f[i] + g[j] + 1 >= maxl)
				--j;
			ans += (f[i] + 1) * (q - j) + sg[j + 1];
			ans += maxl * j;
		}
		printf("%.3f\n", (double)ans / (n * q) + eps);
	}
	return 0;
}
