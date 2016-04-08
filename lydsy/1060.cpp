#include <cstdio>
#include <vector>
using namespace std;
const int maxn = 500001;
int n, s, f[maxn];
long long ans;
vector<pair<int, int> > g[maxn];
void dfs(int u, int fa)
{
	for(vector<pair<int, int> >::iterator it = g[u].begin(); it != g[u].end(); ++it)
	{
		int &v = it -> first, &w = it -> second;
		if(v == fa)
			continue;
		dfs(v, u);
		if(f[u] < f[v] + w)
			f[u] = f[v] + w;
	}
	for(vector<pair<int, int> >::iterator it = g[u].begin(); it != g[u].end(); ++it)
	{
		int &v = it -> first, &w = it -> second;
		if(v == fa)
			continue;
		ans += f[u] - f[v] - w;
	}
}
int main()
{
	scanf("%d%d", &n, &s);
	for(int i = 1, u, v, w; i < n; ++i)
	{
		scanf("%d%d%d", &u, &v, &w);
		g[u].push_back(make_pair(v, w));
		g[v].push_back(make_pair(u, w));
	}
	dfs(s, 0);
	printf("%lld\n", ans);
	return 0;
}
