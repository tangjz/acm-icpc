#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn = 16001;
int n, size[maxn], f[maxn], ans = maxn, cnt;
vector<int> g[maxn];
bool vis[maxn];
void dfs(int u)
{
	vis[u] = 1;
	size[u] = 1;
	for(vector<int>::iterator it = g[u].begin(); it != g[u].end(); ++it)
	{
		int &v = *it;
		if(vis[v])
			continue;
		dfs(v);
		size[u] += size[v];
		if(f[u] < size[v])
			f[u] = size[v];
	}
	if(f[u] < n - size[u])
		f[u] = n - size[u];
}
int main()
{
	scanf("%d", &n);
	for(int i = 1, u, v; i < n; ++i)
	{
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1);
	for(int i = 1; i <= n; ++i)
		if(f[i] < ans)
		{
			ans = f[i];
			cnt = 1;
		}
		else if(f[i] == ans)
			++cnt;
	printf("%d %d\n", ans, cnt);
	bool flag = 0;
	for(int i = 1; i <= n; ++i)
		if(f[i] == ans)
		{
			if(flag)
				putchar(' ');
			else
				flag = 1;
			printf("%d", i);
		}
	putchar('\n');
	return 0;
}
