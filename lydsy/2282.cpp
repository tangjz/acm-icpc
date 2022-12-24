#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 300009;
typedef pair<int, int> Edge;
int n, s, p[maxn], f[maxn], tot, que[maxn], dis[maxn], pre[maxn], suf[maxn], deq[maxn], l, r;
vector<Edge> e[maxn];
bool inq[maxn];
void dfs(int u, int fa)
{
	f[u] = 0;
	for(vector<Edge>::iterator it = e[u].begin(); it != e[u].end(); ++it)
	{
		int &v = it -> first, &w = it -> second;
		if(v == fa || inq[v])
			continue;
		dfs(v, u);
		if(f[u] < f[v] + w)
		{
			f[u] = f[v] + w;
			p[u] = v;
		}
	}
}
int main()
{
	tot = 0;
	scanf("%d%d", &n, &s);
	for(int i = 1; i < n; ++i)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		e[u].push_back(make_pair(v, w));
		e[v].push_back(make_pair(u, w));
	}
	dfs(1, -1);
	for(que[tot++] = 1; f[que[0]]; que[0] = p[que[0]]);
	dfs(que[0], -1);
	inq[que[0]] = 1;
	dis[0] = f[que[0]];
	for(int u = que[0]; f[u]; u = p[u])
	{
		inq[p[u]] = 1;
		dis[tot] = f[p[u]];
		que[tot++] = p[u];
	}
	for(int i = 0; i < tot; ++i)
	{
		dfs(que[i], -1);
		pre[i] = suf[i] = f[que[i]];
	}
	for(int i = 1; i < tot; ++i)
		if(pre[i] < pre[i - 1] + dis[i - 1] - dis[i])
			pre[i] = pre[i - 1] + dis[i - 1] - dis[i];
	for(int i = tot - 2; i >= 0; --i)
		if(suf[i] < suf[i + 1] + dis[i] - dis[i + 1])
			suf[i] = suf[i + 1] + dis[i] - dis[i + 1];
	int ans = ~0u >> 1;
	l = r = 0;
	for(int i = 0, j = 0; i < tot; ++i)
		for(j = j < i ? i : j; j < tot && dis[i] - dis[j] <= s; ++j)
		{
			while(l < r && f[deq[r - 1]] <= f[que[j]])
				--r;
			deq[r++] = que[j];
			int tmp = max(max(pre[i], suf[j]), f[deq[l]]);
			if(ans >= tmp)
				ans = tmp;
			else
			{
				if(l < r && deq[l] == que[i])
					++l;
				break;
			}
		}
	printf("%d\n", ans);
	return 0;
}