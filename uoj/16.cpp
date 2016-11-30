#include <cstdio>
const int maxn = 200001, mod = 10007;
int n, w[maxn], tot, pre[maxn], ans1, ans2;
struct Edge
{
	int nxt, v;
} e[maxn << 1];
void inc(int &x, int y)
{
	x += y;
	if(x >= mod)
		x -= mod;
}
int sqr(int x)
{
	return x * x % mod;
}
void upd(int &x, int y)
{
	if(x < y)
		x = y;
}
void upd(int &x1, int &x2, int y)
{
	if(x1 < y)
	{
		x2 = x1;
		x1 = y;
	}
	else if(x2 < y)
		x2 = y;
}
void dfs(int u, int fa)
{
	int sum1 = 0, sum2 = 0, max1 = 0, max2 = 0;
	if(fa != -1)
	{
		inc(sum1, w[fa]);
		inc(sum2, sqr(w[fa]));
		upd(max1, max2, w[fa]);
	}
	for(int it = pre[u]; it; it = e[it].nxt)
	{
		int &v = e[it].v;
		if(v == fa)
			continue;
		dfs(v, u);
		inc(sum1, w[v]);
		inc(sum2, sqr(w[v]));
		upd(max1, max2, w[v]);
	}
	upd(ans1, max1 * max2);
	int tmp = sqr(sum1) - sum2;
	if(tmp < 0)
		tmp += mod;
	inc(ans2, tmp);
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i < n; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[++tot] = (Edge){pre[u], v};
		pre[u] = tot;
		e[++tot] = (Edge){pre[v], u};
		pre[v] = tot;
	}
	for(int i = 1; i <= n; ++i)
		scanf("%d", w + i);
	dfs(1, -1);
	printf("%d %d\n", ans1, ans2);
	return 0;
}
