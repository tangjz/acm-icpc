#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 10001, maxk = 11;
int n, s, k, f[maxn][maxk];
vector<pair<int, int> > g[maxn];
bool vis[maxn];
void dfs(int u)
{
	vis[u] = 1;
	for(vector<pair<int, int> >::iterator it = g[u].begin(); it != g[u].end(); ++it)
	{
		int &v = it -> first, &w = it -> second;
		if(vis[v])
			continue;
		dfs(v);
		for(int i = k; i >= 0; --i)
		{
			f[u][i] += f[v][0] + 2 * w;
			for(int j = 1; j <= i; ++j)
				if(f[u][i] > f[u][i - j] + f[v][j] + j * w)
					f[u][i] = f[u][i - j] + f[v][j] + j * w;
		}
	}
}
int main()
{
	while(scanf("%d%d%d", &n, &s, &k) == 3)
	{
		memset(f, 0, sizeof f);
		memset(vis, 0, sizeof vis);
		for(int i = 1; i <= n; ++i)
			g[i].clear();
		for(int i = 1, u, v, w; i < n; ++i)
		{
			scanf("%d%d%d", &u, &v, &w);
			g[u].push_back(make_pair(v, w));
			g[v].push_back(make_pair(u, w));
		}
		dfs(s);
		printf("%d\n", f[s][k]);
	}
	return 0;
}
