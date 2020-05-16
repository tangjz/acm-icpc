#include <cstdio>
#include <vector>
#include <algorithm>
const int maxn = 200001;
int n, m, sz[maxn];
long long ans;
std::vector<int> e[maxn];
bool vis[maxn];
void dfs(int u)
{
	vis[u] = 1;
	for(std::vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
	{
		if(vis[*it])
			continue;
		dfs(*it);
		ans += std::min(sz[*it], m - sz[*it]);
		sz[u] += sz[*it];
	}
}
int main()
{
	scanf("%d%d", &n, &m);
	m <<= 1;
	for(int i = 0; i < m; ++i)
	{
		int u;
		scanf("%d", &u);
		++sz[u];
	}
	for(int i = 1; i < n; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1);
	printf("%I64d\n", ans);
	return 0;
}
