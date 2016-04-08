#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = (int)2e4;
int n, f[maxn], ff[maxn], pos[maxn], w[maxn];
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
		if(f[u] < f[v] + w[v])
		{
			pos[u] = v;
			ff[u] = f[u];
			f[u] = f[v] + w[v];
		}
		else if(ff[u] < f[v] + w[v])
			ff[u] = f[v] + w[v];
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
		int &ww = pos[u] == v ? ff[u] : f[u];
		if(f[v] < ww + w[v])
		{
			pos[v] = u;
			ff[v] = f[v];
			f[v] = ww + w[v];
		}
		else if(ff[v] < ww + w[v])
			ff[v] = ww + w[v];
		dfs2(v);
	}
}
int main()
{
	while(scanf("%d", &n) == 1)
	{
		for(int i = 1; i <= n; ++i)
			e[i].clear();
		for(int i = 2; i <= n; ++i)
		{
			int u;
			scanf("%d%d", &u, w + i);
			e[u].push_back(i);
		}
		memset(f, 0, sizeof f);
		memset(ff, 0, sizeof ff);
		memset(pos, 0, sizeof pos);
		memset(vis, 0, sizeof vis);
		dfs1(1);
		memset(vis, 0, sizeof vis);
		dfs2(1);
		for(int i = 1; i <= n; ++i)
			printf("%d\n", f[i]);
	}
	return 0;
}
