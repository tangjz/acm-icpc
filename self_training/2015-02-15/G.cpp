#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 251;
int n, m, q, pos[maxn], g[maxn][maxn], f[maxn][maxn];
struct Node
{
	int id, c;
	bool operator < (const Node &x) const
	{
		return c < x.c;
	}
} a[maxn];
int main()
{
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 1; i <= n; ++i)
	{
		a[i].id = i;
		scanf("%d", &a[i].c);
	}
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; ++i)
		pos[a[i].id] = i;
	memset(g, 0x3f, sizeof g);
	while(m--)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		if(w < g[u = pos[u]][v = pos[v]])
			g[u][v] = g[v][u] = w;
	}
	for(int i = 1; i <= n; ++i)
		g[i][i] = 0;
	memset(f, 0x3f, sizeof f);
	for(int k = 1; k <= n; ++k)
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
				if(g[i][j] >= g[i][k] + g[k][j])
				{
					g[i][j] = g[i][k] + g[k][j];
					int cost = max(a[i].c, max(a[j].c, a[k].c));
					if(f[i][j] > g[i][j] + cost)
						f[i][j] = g[i][j] + cost;
				}
	while(q--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		printf("%d\n", f[pos[u]][pos[v]]);
	}
	return 0;
}
