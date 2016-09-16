#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 500001;
int n, tot, lnk[maxn], f[maxn][3], fro[maxn][2], idx[maxn][2], down[maxn][2], up[maxn][2], ans[2][5];
struct Edge
{
	int nxt, v;
} e[maxn << 1];
void pfs(int u, int fa)
{
	f[u][0] = f[u][1] = 0;
	fro[u][0] = fro[u][1] = idx[u][0] = idx[u][1] = u;
	down[u][0] = -1;
	for(int it = lnk[u]; it != -1; it = e[it].nxt)
	{
		int v = e[it].v;
		if(v == fa)
			continue;
		pfs(v, u);
		if(f[u][0] < f[v][0] + 1)
		{
			f[u][2] = f[u][1];
			f[u][1] = f[u][0];
			fro[u][1] = fro[u][0];
			idx[u][1] = idx[u][0];
			f[u][0] = f[v][0] + 1;
			fro[u][0] = v;
			idx[u][0] = idx[v][0];
		}
		else if(f[u][1] < f[v][0] + 1)
		{
			f[u][2] = f[u][1];
			f[u][1] = f[v][0] + 1;
			fro[u][1] = v;
			idx[u][1] = idx[v][0];
		}
		else if(f[u][2] < f[v][0] + 1)
			f[u][2] = f[v][0] + 1;
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
		int v = e[it].v;
		if(v == fa)
			continue;
		int i = fro[u][0] == v;
		if(f[v][0] < f[u][i] + 1)
		{
			f[v][2] = f[v][1];
			f[v][1] = f[v][0];
			fro[v][1] = fro[v][0];
			idx[v][1] = idx[v][0];
			f[v][0] = f[u][i] + 1;
			fro[v][0] = u;
			idx[v][0] = idx[u][i];
		}
		else if(f[v][1] < f[u][i] + 1)
		{
			f[v][2] = f[v][1];
			f[v][1] = f[u][i] + 1;
			fro[v][1] = u;
			idx[v][1] = idx[u][i];
		}
		else if(f[v][2] < f[u][i] + 1)
			f[v][2] = f[u][i] + 1;
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
		int w = std::max((up[v][0] + 1 >> 1) + (down[v][0] + 1 >> 1) + 1, std::max(up[v][0], down[v][0]));
		if(ans[0][0] > w)
		{
			ans[0][0] = w;
			ans[0][1] = u;
			ans[0][2] = v;
			ans[0][3] = up[v][1];
			ans[0][4] = down[v][1];
		}
		if(ans[1][0] < up[v][0] + down[v][0] + 1)
		{
			ans[1][0] = up[v][0] + down[v][0] + 1;
			ans[1][1] = u;
			ans[1][2] = v;
			ans[1][3] = up[v][1];
			ans[1][4] = down[v][1];
		}
		dfs(v, u);
	}
}
int find(int s, int ban)
{
	int L = 0, R = 0;
	static int que[maxn], dis[maxn], pre[maxn], *path = dis;
	memset(dis + 1, -1, n * sizeof(int));
	dis[s] = 0;
	pre[R] = -1;
	que[R++] = s;
	for( ; L < R; ++L)
	{
		int u = que[L];
		for(int it = lnk[u]; it != -1; it = e[it].nxt)
			if(e[it].v != ban && dis[e[it].v] == -1)
			{
				dis[e[it].v] = dis[u] + 1;
				pre[R] = L;
				que[R++] = e[it].v;
			}
	}
	for(L = 0, --R; R != -1; path[L++] = que[R], R = pre[R]);
	return path[L >> 1];
}
int main()
{
	scanf("%d", &n);
	memset(lnk + 1, -1, n * sizeof(int));
	for(int i = 1; i < n; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[tot] = (Edge){lnk[u], v};
		lnk[u] = tot++;
		e[tot] = (Edge){lnk[v], u};
		lnk[v] = tot++;
	}
	pfs(1, -1);
	up[1][0] = 0;
	up[1][1] = up[1][2] = 1;
	ans[0][0] = maxn;
	ans[1][0] = -1;
	dfs(1, -1);
	for(int i = 3; i < 5; ++i)
		ans[0][i] = find(ans[0][i], ans[0][5 - i]);
	for(int i = 0; i < 2; ++i)
		for(int j = 0; j < 5; ++j)
			printf("%d%c", ans[i][j], " \n"[j == 4]);
	return 0;
}
