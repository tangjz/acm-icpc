#include <cstdio>
typedef long long LL;
const int maxn = 100001, mod = 1000000007;
int n, fa[maxn], sz[maxn];
LL ans;
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		fa[i] = i;
		sz[i] = 1;
	}
	for(int i = 1; i < n; ++i)
	{
		int u, v;
		char op[2];
		scanf("%d%d%s", &u, &v, op);
		if(op[0] == 'b')
		{
			fa[u = find(u)] = (v = find(v));
			sz[v] += sz[u];
		}
	}
	ans = n * (n - 1LL) * (n - 2) / 6;
	for(int i = 1; i <= n; ++i)
		if(i == find(i))
			ans -= sz[i] * (sz[i] - 1LL) * (sz[i] - 2) / 6 + sz[i] * (sz[i] - 1LL) / 2 * (n - sz[i]);
	printf("%d\n", (int)(ans % mod));
	return 0;
}
