#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef pair<int, int> edge;
const int maxn = (int)1e6;
long long n, q, sum[maxn], x[maxn], vis[maxn];
vector<edge> e[maxn];
double ans, fac;
struct Line
{
	long long x, y, w;
} l[maxn];
void dfs(int u)
{
	vis[u] = 1;
	sum[u] = 1;
	for(int i = 0, j = (int)e[u].size(); i < j; ++i)
	{
		int &v = e[u][i].first, &pos = e[u][i].second;
		if(vis[v])
			continue;
		dfs(v);
		sum[u] += sum[v];
		if(!l[pos].x)
		{
			l[pos].x = sum[v];
			l[pos].y = n - sum[v];
		}
	}
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i < n; ++i)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		l[i].w = w;
		e[u].push_back(make_pair(v, i));
		e[v].push_back(make_pair(u, i));
	}
	dfs(1);
	for(int i = 1; i < n; ++i)
		ans += (long long)l[i].x * l[i].y * l[i].w;
	scanf("%d", &q);
	while(q--)
	{
		int pos, val;
		scanf("%d%d", &pos, &val);
		ans -= (long long)l[pos].x * l[pos].y * l[pos].w;
		l[pos].w = val;
		ans += (long long)l[pos].x * l[pos].y * l[pos].w;
		printf("%.9f\n", ans * 6 / n / (n - 1));
	}
	return 0;
}
