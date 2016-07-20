#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 151;
int n, m, tot, seq[maxn];
bool vis[maxn], e[maxn][maxn];
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		tot = 0;
		memset(vis + 1, 0, n * sizeof(bool));
		for(int i = 1; i <= n; ++i)
			memset(e[i] + 1, 0, n * sizeof(bool));
		while(m--)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			e[u][v] = e[v][u] = 1;
		}
		tot = 0;
		vis[1] = 1;
		seq[tot++] = 1;
		while(tot >= 0)
		{
			for(int u = seq[tot - 1], &v = ++seq[tot]; v <= n && !(!vis[v] && e[u][v]); ++v);
			if(seq[tot] > n)
			{
				seq[tot] = 0;
				vis[seq[--tot]] = 0;
				continue;
			}
			vis[seq[tot++]] = 1;
			if(tot == n && e[seq[tot - 1]][seq[0]])
				break;
		}
		if(tot < n)
			puts("no solution");
		else
			for(int i = 0; i < n; ++i)
				printf("%d%c", seq[i], " \n"[i == n - 1]);
	}
	return 0;
}
