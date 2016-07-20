#include <cstdio>
const int maxn = 10001, maxm = 200001;
int n, tot, deg[maxn], lnk[maxn], c[maxn][2], f[maxn], g[maxn], h[maxn], que[maxn << 1], L, R;
struct Edge
{
	int nxt, v;
} e[maxm];
int main()
{
	scanf("%d", &n);
	for(int i = 2; i < n; ++i)
	{
		scanf("%d", deg + i);
		c[i][0] = deg[i];
		for(int j, k = 0; k < deg[i]; ++k)
		{
			scanf("%d", &j);
			e[++tot] = (Edge){lnk[j], i};
			lnk[j] = tot;
		}
	}
	L = R = 0;
	g[1] = 1;
	que[R++] = 1;
	while(L < R)
	{
		int u = que[L++];
		for(int it = lnk[u]; it; it = e[it].nxt)
		{
			int v = e[it].v;
			if(f[u] != -1)
				--c[v][f[u]];
			if(g[u] != -1)
				++c[v][g[u]];
			int w = c[v][0] == c[v][1] ? -1 : c[v][0] < c[v][1];
			if(g[v] != w)
			{
				if(f[v] == g[v])
					que[R++] = v;
				g[v] = w;
			}
		}
		f[u] = g[u];
	}
	for(int i = 0; i < n; ++i)
	{
		c[i][0] = 0;
		c[i][1] = deg[i];
		f[i] = h[i] = 1;
	}
	L = R = 0;
	h[0] = 0;
	que[R++] = 0;
	while(L < R)
	{
		int u = que[L++];
		for(int it = lnk[u]; it; it = e[it].nxt)
		{
			int v = e[it].v;
			if(f[u] != -1)
				--c[v][f[u]];
			if(h[u] != -1)
				++c[v][h[u]];
			int w = c[v][0] == c[v][1] ? -1 : c[v][0] < c[v][1];
			if(h[v] != w)
			{
				if(f[v] == h[v])
					que[R++] = v;
				h[v] = w;
			}
		}
		f[u] = h[u];
	}
	for(int i = 0; i < n; ++i)
		if(g[i] != h[i])
			puts("?");
		else if(g[i] < 0)
			puts("1/2");
		else
			printf("%d\n", g[i]);
	return 0;
}
