#include <cstdio>
#include <cstring>
const int maxn = 201;
int n, tot, lnk[maxn], idx, ans;
struct Edge
{
	int nxt, v;
} e[maxn << 1];
bool vis[maxn];
int dfs(int u, int &ans)
{
	vis[u] = 1;
	int mx1 = 0, mx2 = 0;
	for(int it = lnk[u]; it != -1; it = e[it].nxt)
	{
		if((it >> 1) == idx || vis[e[it].v])
			continue;
		int val = dfs(e[it].v, ans) + 1;
		if(mx1 < val)
		{
			mx2 = mx1;
			mx1 = val;
		}
		else if(mx2 < val)
			mx2 = val;
	}
	if(ans < mx1 + mx2)
		ans = mx1 + mx2;
	return mx1;
}
int main()
{
	scanf("%d", &n);
	memset(lnk, -1, sizeof lnk);
	for(int i = 1; i < n; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[tot] = (Edge){lnk[u], v};
		lnk[u] = tot++;
		e[tot] = (Edge){lnk[v], u};
		lnk[v] = tot++;
	}
	for(int i = 0; i < tot; i += 2)
	{
		idx = i >> 1;
		int x = 0, y = 0;
		memset(vis, 0, sizeof vis);
		dfs(e[idx << 1].v, x);
		dfs(e[idx << 1 | 1].v, y);
		if(ans < x * y)
			ans = x * y;
	}
	printf("%d\n", ans);
	return 0;
}
