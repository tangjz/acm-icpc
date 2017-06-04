#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 2001, maxm = 2000001;
int n, m, q, ord[maxn], x[maxn], y[maxn];
int tot, pre[maxn], rev[maxn], seq[maxn], scc[maxn];
bool vis[maxn];
struct Edge {
	int nxt, v;
} e[maxm << 1 | 1];
void addEdge(int u, int v)
{
	// printf("%d -> %d\n", u, v);
	e[tot] = (Edge){pre[u], v};
	pre[u] = tot++;
	e[tot] = (Edge){rev[v], u};
	rev[v] = tot++;
}
void dfs1(int u)
{
	vis[u] = 1;
	for(int it = pre[u]; it != -1; it = e[it].nxt)
		if(!vis[e[it].v])
			dfs1(e[it].v);
	seq[tot++] = u;
}
void dfs2(int u)
{
	scc[u] = tot;
	for(int it = rev[u]; it != -1; it = e[it].nxt)
		if(scc[e[it].v] == -1)
			dfs2(e[it].v);
}
bool cmp(int const &u, int const &v)
{
	return x[u] < x[v] || (x[u] == x[v] && y[u] < y[v]);
}
int main()
{
	scanf("%d%d%d", &m, &q, &n);
	memset(pre, -1, sizeof pre);
	memset(rev, -1, sizeof rev);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d%d", x + i, y + i);
		ord[i] = i;
	}
	sort(ord, ord + n, cmp);
	for(int i = 0, j = 0; i < n; i = j)
	{
		for( ; j < n && x[ord[i]] == x[ord[j]]; ++j);
		for(int u = i; u < j; ++u)
			for(int v = u + 1; v < j; ++v)
				if(y[ord[v]] - y[ord[u]] <= (q << 1))
				{
					addEdge(n + ord[v], ord[u]);
					addEdge(n + ord[u], ord[v]);
				}
	}
	for(int i = 0; i < n; ++i)
		swap(x[i], y[i]);
	sort(ord, ord + n, cmp);
	for(int i = 0, j = 0; i < n; i = j)
	{
		for( ; j < n && x[ord[i]] == x[ord[j]]; ++j);
		for(int u = i; u < j; ++u)
			for(int v = u + 1; v < j; ++v)
				if(y[ord[v]] - y[ord[u]] <= (q << 1))
				{
					addEdge(ord[v], n + ord[u]);
					addEdge(ord[u], n + ord[v]);
				}
	}
	n <<= 1;
	tot = 0;
	for(int i = 0; i < n; ++i)
		if(!vis[i])
			dfs1(i);
	tot = 0;
	memset(scc, -1, sizeof scc);
	for(int i = n - 1; i >= 0; --i)
		if(scc[seq[i]] == -1)
		{
			dfs2(seq[i]);
			tot++;
		}
	n >>= 1;
	bool flag = 1;
	for(int i = 0; i < n; ++i)
		flag &= scc[i] != scc[n + i];
	puts(flag ? "YES" : "NO");
	return 0;
}
