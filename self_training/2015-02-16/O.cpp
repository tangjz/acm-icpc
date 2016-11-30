#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1001, maxm = 201, maxk = 51;
int t, n, m, f[maxn][maxm], g[maxn][maxm];
vector<int> e[maxn];
bool vis[maxn];
void dfs(int u)
{
	vis[u] = 1;
	if(e[u].size() == 1 && u != 1)
		return;
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
		if(!vis[*it])
		{
			int &v = *it;
			dfs(v);
			for(int i = m; i >= 0; --i)
			{
				if(g[u][i] > f[v][0])//j = 0
					g[u][i] = f[v][0];
				for(int j = 1; j <= i; ++j)
				{
					int tmp = g[u][i - j] < f[v][j] ? g[u][i - j] : f[v][j];
					if(g[u][i] < tmp)
						g[u][i] = tmp;
				}
			}
		}
	for(int i = m; i >= 0; --i)
		for(int j = 0; j <= i; ++j)
			if(f[u][i] < f[u][i - j] + g[u][j])
				f[u][i] = f[u][i - j] + g[u][j];
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		memset(f, 0, sizeof f);
		memset(vis, 0, sizeof vis);
		memset(g, 0x3f, sizeof g);
		for(int i = 1; i <= n; ++i)
			e[i].clear();
		scanf("%d", &n);
		for(int i = 1, u, v; i < n; ++i)
		{
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
		scanf("%d", &m);
		for(int i = 1; i <= n; ++i)
		{
			int s, c, w;
			scanf("%d", &s);
			for(int j = 0; j < s; ++j)
			{
				scanf("%d%d", &c, &w);
				if(f[i][c] < w)
					f[i][c] = w;
			}
			for(int j = 1; j <= m; ++j)
				if(f[i][j] < f[i][j - 1])
					f[i][j] = f[i][j - 1];
		}
		dfs(1);
		printf("%d\n", f[1][m]);
	}
	return 0;
}
