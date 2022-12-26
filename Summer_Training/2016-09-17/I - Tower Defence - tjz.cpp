#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxn = 100001;
int t, n, tot, lnk[maxn], f[maxn][3], fro[maxn][2], idx[maxn][2], down[maxn][2], up[maxn][2];
LL ans;
struct Edge
{
	int nxt, v, w;
} e[maxn << 1];
void pfs(int u, int fa)
{
	f[u][0] = f[u][1] = f[u][2] = 0;
	fro[u][0] = fro[u][1] = idx[u][0] = idx[u][1] = u;
	down[u][0] = -1;
	for(int it = lnk[u]; it != -1; it = e[it].nxt)
	{
		int v = e[it].v, w = e[it].w;
		if(v == fa)
			continue;
		pfs(v, u);
		if(f[u][0] < f[v][0] + w)
		{
			f[u][2] = f[u][1];
			f[u][1] = f[u][0];
			fro[u][1] = fro[u][0];
			idx[u][1] = idx[u][0];
			f[u][0] = f[v][0] + w;
			fro[u][0] = v;
			idx[u][0] = idx[v][0];
		}
		else if(f[u][1] < f[v][0] + w)
		{
			f[u][2] = f[u][1];
			f[u][1] = f[v][0] + w;
			fro[u][1] = v;
			idx[u][1] = idx[v][0];
		}
		else if(f[u][2] < f[v][0] + w)
			f[u][2] = f[v][0] + w;
		if(down[u][0] < down[v][0])
		{
			down[u][0] = down[v][0];
			down[u][1] = down[v][1];
		}
	}
	if(down[u][0] < f[u][0] + f[u][1])
	{
		down[u][0] = f[u][0] + f[u][1];
		down[u][1] = idx[u][0];
	}
	// printf("down %d : %d %d\n", u, down[u][0], down[u][1]);
}
void dfs(int u, int fa)
{
	int cur[2][2] = {}, cidx = u;
	cur[0][0] = up[u][0];
	cur[0][1] = up[u][1];
	for(int it = lnk[u]; it != -1; it = e[it].nxt)
	{
		int v = e[it].v;
		if(v == fa)
			continue;
		if(cur[0][0] < down[v][0])
		{
			cur[1][0] = cur[0][0];
			cur[1][1] = cur[0][1];
			cur[0][0] = down[v][0];
			cur[0][1] = down[v][1];
			cidx = v;
		}
		else if(cur[1][0] < down[v][0])
		{
			cur[1][0] = down[v][0];
			cur[1][1] = down[v][1];
		}
	}
	for(int it = lnk[u]; it != -1; it = e[it].nxt)
	{
		int v = e[it].v, w = e[it].w;
		if(v == fa)
			continue;
		int i = fro[u][0] == v;
		if(f[v][0] < f[u][i] + w)
		{
			f[v][2] = f[v][1];
			f[v][1] = f[v][0];
			fro[v][1] = fro[v][0];
			idx[v][1] = idx[v][0];
			f[v][0] = f[u][i] + w;
			fro[v][0] = u;
			idx[v][0] = idx[u][i];
		}
		else if(f[v][1] < f[u][i] + w)
		{
			f[v][2] = f[v][1];
			f[v][1] = f[u][i] + w;
			fro[v][1] = u;
			idx[v][1] = idx[u][i];
		}
		else if(f[v][2] < f[u][i] + w)
			f[v][2] = f[u][i] + w;
		int k = cidx == v;
		up[v][0] = cur[k][0];
		up[v][1] = cur[k][1];
		int j = (i || fro[u][1] == v) + 1;
		if(up[v][0] < f[u][i] + f[u][j])
		{
			up[v][0] = f[u][i] + f[u][j];
			up[v][1] = idx[u][i];
		}
		// printf("up %d : %d %d\n", v, up[v][0], up[v][1]);
		ans += std::max(up[v][0], down[v][0]);
		// printf("%d : %d %d\n", v, up[v][0], down[v][0]);
		dfs(v, u);
	}
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		tot = 0;
		memset(lnk + 1, -1, n * sizeof(int));
		for(int i = 1; i < n; ++i)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			e[tot] = (Edge){lnk[u], v, w};
			lnk[u] = tot++;
			e[tot] = (Edge){lnk[v], u, w};
			lnk[v] = tot++;
		}
		pfs(1, -1);
		up[1][0] = 0;
		up[1][1] = 1;
		ans = 0;
		dfs(1, -1);
		printf("%I64d\n", ans);
	}
	return 0;
}
