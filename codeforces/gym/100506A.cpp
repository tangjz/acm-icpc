#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef pair<int, int> edge;
const int maxn = 10001;
struct Line
{
	int x, y, w;
} l[maxn];
int t, n, size[maxn];
vector<edge> e[maxn];
bool vis[maxn];
double ans;
void dfs(int u)
{
	vis[u] = 1;
	size[u] = 1;
	for(int i = 0, j = (int)e[u].size(); i < j; ++i)
	{
		int &v = e[u][i].first, &pos = e[u][i].second;
		if(vis[v])
			continue;
		dfs(v);
		size[u] += size[v];
		if(!l[pos].x)
		{
			l[pos].x = size[v];
			l[pos].y = n - size[v];
		}
	}
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		ans = 0;
		memset(vis, 0, sizeof vis);
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			e[i].clear();
		for(int i = 1; i < n; ++i)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			l[i].w = w;
			l[i].x = 0;
			e[u].push_back(make_pair(v, i));
			e[v].push_back(make_pair(u, i));
		}
		dfs(0);
		for(int i = 1; i < n; ++i)
			ans += 1.0 * l[i].x * l[i].y * l[i].w;
		printf("%.8f\n", ans / (n * (n - 1) / 2));
	}
	return 0;
}
