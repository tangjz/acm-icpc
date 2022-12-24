#include <cstdio>
const int maxn = 100010, maxd = 17, mod = 1000000007;
typedef long long LL;
int n, q, tot, pre[maxn], dep[maxn], fa[maxn][maxd], seed1, seed2, pw1[maxn], pw2[maxn], h1[maxn], h2[maxn];
char str[maxn];
struct Edge
{
	int nxt, v;
} e[maxn << 1];
int inv(int x)
{
	return x <= 1 ? x : mod - (LL)mod / x * inv(mod % x) % mod;
}
void dfs(int u)
{
	for(int it = pre[u]; it; it = e[it].nxt)
	{
		int &v = e[it].v;
		if(dep[v])
			continue;
		dep[v] = dep[u] + 1;
		fa[v][0] = u;
		for(int d = 1; d < maxd && fa[v][d - 1]; ++d)
			fa[v][d] = fa[fa[v][d - 1]][d - 1];
		h1[v] = ((LL)h1[u] * seed1 + (str[v] - 'a' + 1)) % mod;
		h2[v] = ((LL)h2[u] * seed2 + (str[v] - 'a' + 1)) % mod;
		dfs(v);
	}
}
int lca(int u, int v)
{
	if(dep[u] > dep[v])
	{
		u = u + v;
		v = u - v;
		u = u - v;
	}
	for(int i = 0, j = dep[v] - dep[u]; i < maxd && j; ++i, j >>= 1)
		if(j & 1)
			v = fa[v][i];
	if(u == v)
		return u;
	for(int d = maxd - 1; d >= 0; --d)
		if(fa[u][d] != fa[v][d])
		{
			u = fa[u][d];
			v = fa[v][d];
		}
	return fa[u][0];
}
int Hash(int u, int v)
{
	int pp = lca(u, v), distu = dep[u] - dep[pp], distv = dep[v] - dep[pp];
	int ret1 = h1[u] - (LL)pw1[distu + 1] * h1[fa[pp][0]] % mod;
	int ret2 = h2[v] - (LL)pw2[distv] * h2[pp] % mod;
	if(ret1 < 0)
		ret1 += mod;
	if(ret2 < 0)
		ret2 += mod;
	return (ret1 + (LL)pw1[distu] * pw1[distv] % mod * ret2) % mod;
}
int main()
{
	scanf("%d%s", &n, str + 1);
	pw1[0] = pw2[0] = 1;
	seed1 = 29, seed2 = inv(seed1);
	for(int i = 1; i <= n; ++i)
	{
		pw1[i] = (LL)pw1[i - 1] * seed1 % mod;
		pw2[i] = (LL)pw2[i - 1] * seed2 % mod;
	}
	for(int i = 1; i < n; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[++tot] = (Edge){pre[u], v};
		pre[u] = tot;
		e[++tot] = (Edge){pre[v], u};
		pre[v] = tot;
	}
	dep[1] = 1;
	h1[1] = h2[1] = str[1] - 'a' + 1;
	dfs(1);
	scanf("%d", &q);
	while(q--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		puts(Hash(u, v) == Hash(v, u) ? "True" : "False");
	}
	return 0;
}
