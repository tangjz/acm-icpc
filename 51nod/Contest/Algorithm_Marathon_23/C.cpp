#include <vector>
#include <stdio.h>
#include <algorithm>
#include <functional>
using namespace std;
typedef pair<int, int> Node;
const int maxn = 400001;
int n, m, q, S, a[maxn], tot, seq[maxn], scc[maxn], deg[maxn], que[maxn], L, R, out[maxn];
Node val[maxn], ans[maxn];
vector<int> e[maxn], g[maxn];
bool vis[maxn];
void dfs1(int u)
{
	vis[u] = 1;
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
		if(!vis[*it])
			dfs1(*it);
	seq[++tot] = u;
}
void dfs2(int u)
{
	scc[u] = tot;
	if(val[tot].first < a[u])
		val[tot] = make_pair(a[u], val[tot].first);
	else if(a[u] < val[tot].first && val[tot].second < a[u])
		val[tot].second = a[u];
	for(vector<int>::iterator it = g[u].begin(); it != g[u].end(); ++it)
		if(!scc[*it])
			dfs2(*it);
}
inline void merge(Node &u, Node v, bool flag = 0)
{
	bool com = u.first != -1 && (u.first == v.first || u.first == v.second)
			|| u.second != -1 && (u.second == v.first || u.second == v.second);
	if(!flag)
	{
		if(u.first < v.first)
		{
			if(v.second < u.first)
				u = make_pair(v.first, u.first);
			else
				u = v;
		}
		else if(u.first == v.first && u.second < v.second)
			u.second = v.second;
		else if(v.first < u.first && u.second < v.first)
			u.second = v.first;
	}
	else
	{
		if(u.first != v.first)
			u = make_pair(max(u.first, v.first), min(u.first, v.first));
		else
			u.second = max(u.second, v.second);
	}
	if(com && u.second == -1)
		u.second = 0;
}
inline void upd(int &x, int y)
{
	if(x < y)
		x = y;
}
int main()
{
	scanf("%d%d%d%d", &n, &m, &q, &S);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	while(m--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		g[v].push_back(u);
	}
	for(int i = 1; i <= n; ++i)
		if(!vis[i])
			dfs1(i);
	tot = 0;
	for(int i = n; i >= 1; --i)
		if(!scc[seq[i]])
		{
			val[++tot] = make_pair(-1, -1);
			dfs2(seq[i]);
		}
	for(int i = 1; i <= tot; ++i)
	{
		vis[i] = 0;
		vector<int>().swap(g[i]);
		ans[i] = make_pair(-1, -1);
		out[i] = -1;
	}
	for(int i = 1; i <= n; ++i)
		for(vector<int>::iterator it = e[i].begin(); it != e[i].end(); ++it)
			if(scc[i] != scc[*it])
				g[scc[i]].push_back(scc[*it]);
	for(int i = 1; i <= tot; ++i)
	{
		sort(g[i].begin(), g[i].end());
		unique(g[i].begin(), g[i].end());
		for(vector<int>::iterator it = g[i].begin(); it != g[i].end(); ++it)
			++deg[*it];
	}
	for(int i = 1; i <= tot; ++i)
		if(!deg[i])
			que[R++] = i;
	while(L < R)
	{
		int u = que[L++];
		if(u == scc[S] || ans[u].first != -1)
		{
			merge(ans[u], val[u]);
			upd(out[u], val[u].second);
		}
		//printf("%d : %d %d %d\n", u, ans[u].first, ans[u].second, out[u]);
		for(vector<int>::iterator it = g[u].begin(); it != g[u].end(); ++it)
		{
			int v = *it;
			Node tmp = ans[u];
			merge(tmp, val[v], 1);
			upd(out[v], tmp.second);
			upd(out[v], out[u]);
			merge(ans[v], ans[u]);
			if(!(--deg[v]))
				que[R++] = v;
		}
	}
	for(int i = 1, x; i <= q; ++i)
	{
		scanf("%d", &x);
		printf("%d%c", out[scc[x]], " \n"[i == q]);
	}
	return 0;
}
