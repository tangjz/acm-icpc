#include <vector>
#include <cstdio>
#include <algorithm>
const int maxn = 100010, maxd = 18, maxs = 11;
struct List
{
	int len, val[maxs];
	void insert(int x)
	{
		if(len < maxs)
			val[len++] = x;
	}
	List merge(const List &t) const
	{
		List ret = {std::min(len + t.len, maxs)};
		for(int i = 0, j = 0, k = 0; (i < len || j < t.len) && k < ret.len; ++k)
			if(j >= t.len || i < len && val[i] <= t.val[j])
				ret.val[k] = val[i++];
			else
				ret.val[k] = t.val[j++];
		return ret;
	}
} st[maxd][maxn], ans;
int n, m, q, dep[maxn], fa[maxd][maxn];
std::vector<int> e[maxn];
void dfs(int u)
{
	for(std::vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
	{
		int v = *it;
		if(v == fa[0][u])
			continue;
		dep[v] = dep[u] + 1;
		fa[0][v] = u;
		for(int d = 1; fa[d - 1][v]; ++d)
		{
			fa[d][v] = fa[d - 1][fa[d - 1][v]];
			st[d][v] = st[d - 1][v].merge(st[d - 1][fa[d - 1][v]]);
		}
		dfs(v);
	}
}
void query(int u, int v, List &ans)
{
	ans = (List){0};
	if(dep[u] > dep[v])
		std::swap(u, v);
	for(int d = 0, i = dep[v] - dep[u]; i > 0; ++d, i >>= 1)
		if(i & 1)
		{
			ans = ans.merge(st[d][v]);
			v = fa[d][v];
		}
	if(u == v)
	{
		ans = ans.merge(st[0][u]);
		return;
	}
	for(int d = maxd - 1; d >= 0; --d)
		if(fa[d][u] != fa[d][v])
		{
			ans = ans.merge(st[d][u]);
			u = fa[d][u];
			ans = ans.merge(st[d][v]);
			v = fa[d][v];
		}
	ans = ans.merge(st[0][u]).merge(st[0][v]).merge(st[0][fa[0][u]]);
}
int main()
{
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 1; i < n; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for(int i = 1; i <= m; ++i)
	{
		int x;
		scanf("%d", &x);
		st[0][x].insert(i);
	}
	dfs(1);
	while(q--)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		query(u, v, ans);
		if(w > ans.len)
			w = ans.len;
		printf("%d", w);
		for(int i = 0; i < w; ++i)
			printf(" %d", ans.val[i]);
		putchar('\n');
	}
	return 0;
}
