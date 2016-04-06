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
	scanf("%d", &n);
	n = (1 << n + 1) - 1;
	for(int i = 2, w; i <= n; ++i)
	{
		scanf("%d", &w);
		g[i].push_back(make_pair(i >> 1, w));
		g[i >> 1].push_back(make_pair(i, w));
	}
	dfs(1, 0);
	printf("%I64d\n", ans);
	return 0;
}
