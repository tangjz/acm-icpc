#include <vector>
#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 50001, maxm = 200001, maxd = 60;
int n, m;
LL f[maxn], g[maxm];
vector<pair<int, LL> > e[maxn];
bool vis[maxn];
void dfs(int u)
{
	vis[u] = 1;
	for(vector<pair<int, LL> >::iterator it = e[u].begin(); it != e[u].end(); ++it)
	{
		int v = it -> first;
		LL w = it -> second;
		if(vis[v])
		{
			g[m++] = f[u] ^ f[v] ^ w;
			continue;
		}
		f[v] = f[u] ^ w;
		dfs(v);
	}
}
int main()
{
	scanf("%d%d", &n, &m);
	while(m--)
	{
		int u, v;
		LL w;
		scanf("%d%d%lld", &u, &v, &w);
		e[u].push_back(make_pair(v, w));
		e[v].push_back(make_pair(u, w));
	}
	m = 0;
	dfs(1);
	std::sort(g, g + m);
	m = std::unique(g, g + m) - g;
	int r = 0;
	for(int i = maxd - 1; i >= 0; --i)
	{
		int k = -1;
		for(int j = r; j < m; ++j)
			if((g[j] >> i) & 1)
			{
				k = j;
				break;
			}
		if(k == -1)
			continue;
		swap(g[r], g[k]);
		for(int j = 0; j < m; ++j)
			if(j != r && (g[j] >> i) & 1)
				g[j] ^= g[r];
		++r;
	}
	LL ans = f[n];
	for(int i = 0; i < r; ++i)
		if(ans < (ans ^ g[i]))
			ans ^= g[i];
	printf("%lld\n", ans);
	return 0;
}
