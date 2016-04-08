#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 10001;
int n, m, tot, scc[maxn], ans;
vector<int> g[maxn], rg[maxn], seq;
bool vis[maxn];
void dfs1(int u)
{
	vis[u] = 1;
	for(vector<int>::iterator it = g[u].begin(); it != g[u].end(); ++it)
		if(!vis[*it])
			dfs1(*it);
	seq.push_back(u);
}
void dfs2(int u)
{
	vis[u] = 1;
	scc[u] = tot;
	for(vector<int>::iterator it = rg[u].begin(); it != rg[u].end(); ++it)
		if(!vis[*it])
			dfs2(*it);
}
int main()
{
	int u, v;
	scanf("%d%d", &n, &m);
	while(m--)
	{
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
		rg[v].push_back(u);
	}
	for(int i = 1; i <= n; ++i)
		if(!vis[i])
			dfs1(i);
	memset(vis, 0, sizeof vis);
	for(vector<int>::iterator it = --seq.end(); it >= seq.begin(); --it)
		if(!vis[*it])
		{
			++tot;
			dfs2(*it);
		}
	for(int i = 1; i <= n; ++i)
		if(scc[i] == tot)
		{
			++ans;
			u = i;
		}
	memset(vis, 0, sizeof vis);
	dfs2(u);
	for(int i = 1; i <= n; ++i)
		if(!vis[i])
		{
			ans = 0;
			break;
		}
	printf("%d\n", ans);
	return 0;
}
