#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn = 16001;
int n, f[maxn], ans = 0xf3f3f3f3;
vector<int> g[maxn];
bool vis[maxn];
void dfs(int u)
{
	vis[u] = 1;
	for(vector<int>::iterator it = g[u].begin(); it != g[u].end(); ++it)
	{
		int &v = *it;
		if(vis[v])
			continue;
		dfs(v);
		if(f[v] > 0)
			f[u] += f[v];
	}
	if(ans < f[u])
		ans = f[u];
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", f + i);
	for(int i = 1, u, v; i < n; ++i)
	{
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1);
	printf("%d\n", ans);
	return 0;
}
