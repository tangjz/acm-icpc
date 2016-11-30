#include <cstdio>
#include <algorithm>
typedef long long LL;
const int maxn = 1001;
int t, n, x[maxn], y[maxn], r[maxn], fa[maxn], dis[maxn];
bool vis[maxn];
int find(int x)
{
	if(x == fa[x])
		return x;
	int tmp = fa[x];
	fa[x] = find(fa[x]);
	dis[x] ^= dis[tmp];
	return fa[x];
}
inline LL sqr(int x)
{
	return (LL)x * x;
}
void dfs(int u)
{
	vis[u] = 1;
	for(int i = 1; i <= n; ++i)
		if(!vis[i] && sqr(x[i] - x[u]) + sqr(y[i] - y[u]) <= sqr(r[i] + r[u]))
				dfs(i);
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d%d%d", x + i, y + i, r + i);
			fa[i] = i;
			dis[i] = 0;
			vis[i] = 0;
		}
		dfs(1);
		bool flag = vis[n];
		for(int i = 1; i <= n && flag; ++i)
		{
			if(!vis[i])
				continue;
			for(int j = i + 1; j <= n && flag; ++j)
			{
				if(!vis[j] || sqr(x[i] - x[j]) + sqr(y[i] - y[j]) > sqr(r[i] + r[j]))
					continue;
				int u = find(i), v = find(j);
				if(u == v)
					flag &= dis[i] != dis[j];
				else
				{
					fa[u] = v;
					dis[u] = dis[i] ^ dis[j] ^ 1;
				}
			}
		}
		if(flag && find(1) == find(n))
		{
			int fz = r[1], fm = r[n], rr = std::__gcd(fz, fm);
			printf("%d/%d %s\n", fz / rr, fm / rr, dis[1] == dis[n] ? "clockwise" : "counterclockwise");
		}
		else
			puts("does not rotate");
	}
	return 0;
}
