#include <cstdio>
struct Line { int v, next; } line[400002];
int n, m, p, head[400001], tot, fa[400001], kill[400001], ans[400001];
bool vis[400001];
inline int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
int main()
{
	int u, v, sum = 0;
	scanf("%d%d", &n, &m);
	while(m--)
	{
		scanf("%d%d", &u, &v);
		line[++tot] = (Line){v, head[u]}; head[u] = tot;
		line[++tot] = (Line){u, head[v]}; head[v] = tot;
	}
	scanf("%d", &p);
	for(int i = 0; i < n; ++i) fa[i] = i;
	for(int i = 0; i < p; ++i) { scanf("%d", &kill[i]); vis[kill[i]] = 1; }
	for(int i = 0; i < n; ++i)
		if(!vis[i])
			for(int j = head[i]; j; j = line[j].next)
				if(!vis[line[j].v]) fa[find(i)] = find(line[j].v);
	for(int i = 0; i < n; ++i) if(!vis[i] && i == find(i)) ++sum;
	ans[p] = sum;
	for(int i = p - 1; i >= 0; --i)
	{
		++sum;
		for(int j = head[kill[i]]; j; j = line[j].next)
			if(!vis[line[j].v])
			{
				int u = find(kill[i]), v = find(line[j].v);
				if(u != v) {fa[u] = v; --sum; }
			}
		ans[i] = sum;
		vis[kill[i]] = 0;
	}
	for(int i = 0; i <= p; ++i) printf("%d\n", ans[i]);
	return 0;
}