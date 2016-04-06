#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 500010;
int n, m, tot, pre[maxn], cnt;
long long f[maxn];
struct Edge
{
	int nxt, v, w;
} e[maxn << 1];
void addedge(int u, int v, int w)
{
	e[tot] = (Edge){pre[u], v, w};
	pre[u] = tot++;
	e[tot] = (Edge){pre[v], u, w};
	pre[v] = tot++;
}
vector<pair<int, int> > h[maxn];
void dfs(int u, int fa)
{
	for(int it = pre[u]; it != -1; it = e[it].nxt)
	{
		int &v = e[it].v, &w = e[it].w;
		if(v == fa || !w)
			continue;
		dfs(v, u);
		h[u].push_back(make_pair(f[v] + w, it));
	}
	if(!h[u].size())
		return;
	sort(h[u].begin(), h[u].end());
	int pos = 0;
	for(int t = h[u].size() - 2; t >= 0; --t)
	{
		if(h[u][t].first + h[u][t + 1].first > m)
		{
			++cnt;
			int &it = h[u][t + 1].second;
			e[it].w = e[it ^ 1].w = 0;
		}
		else
		{
			pos = t + 1;
			break;
		}
	}
	if(!pos && h[u][pos].first > m)
	{
		++cnt;
		int &it = h[u][pos].second;
		e[it].w = e[it ^ 1].w = 0;
	}
	else
		f[u] = h[u][pos].first;
}
int main()
{
	scanf("%d%d", &n, &m);
	memset(pre, -1, sizeof pre);
	for(int i = 1; i < n; ++i)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		addedge(u, v, w);
	}
	cnt = 1;
	dfs(0, -1);
	printf("%d\n", cnt);
	return 0;
}
