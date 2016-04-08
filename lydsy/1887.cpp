#include <cstdio>
typedef long long LL;
const int maxn = 100001, mod = 1000000007;
int n, tot, pre[maxn], f[maxn], ans;
struct Edge
{
	int nxt, v, w;
} e[maxn << 1];
void dfs(int u, int fa)
{
	for(int it = pre[u]; it; it = e[it].nxt)
	{
		int &v = e[it].v;
		if(v == fa)
			continue;
		dfs(v, u);
		int tmp = (f[v] + 1LL) * e[it].w % mod;
		ans = (ans + (LL)f[u] * tmp) % mod;
		f[u] += tmp;
		if(f[u] >= mod)
			f[u] -= mod;
	}
	ans += f[u];
	if(ans >= mod)
		ans -= mod;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i < n; ++i)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		e[++tot] = (Edge){pre[u], v, w};
		pre[u] = tot;
		e[++tot] = (Edge){pre[v], u, w};
		pre[v] = tot;
	}
	dfs(1, -1);
	printf("%d\n", ans);
	return 0;
}
