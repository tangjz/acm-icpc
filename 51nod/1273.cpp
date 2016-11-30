#include <stdio.h>
const int maxn = 50001;
int n, s, tot, lnk[maxn], dis[maxn], cnt[maxn], *ord = lnk;
struct Edge
{
	int nxt, v;
} e[maxn << 1];
int dfs(int u, int fa)
{
	int fro = u;
	for(int it = lnk[u]; it; it = e[it].nxt)
	{
		if(e[it].v == fa)
			continue;
		int tmp = dfs(e[it].v, u);
		if(dis[fro] < dis[tmp] || dis[fro] == dis[tmp] && tmp < fro)
			fro = tmp;
	}
	++dis[fro];
	return fro;
}
int main()
{
	scanf("%d%d", &n, &s);
	if(n == 1)
	{
		puts("0");
		return 0;
	}
	for(int i = 1; i < n; ++i)
	{
		int fa;
		scanf("%d", &fa);
		e[++tot] = (Edge){lnk[i], fa};
		lnk[i] = tot;
		e[++tot] = (Edge){lnk[fa], i};
		lnk[fa] = tot;
	}
	dfs(s, -1);
	for(int i = 0; i < n; ++i)
		++cnt[dis[i]];
	for(int i = 1; i <= n; ++i)
		cnt[i] += cnt[i - 1];
	for(int i = 0; i < n; ++i)
		ord[--cnt[dis[i]]] = i;
	printf("%d\n", s);
	for(int i = n - 1; i >= 0 && dis[ord[i]]; --i)
		printf("%d\n", ord[i]);
	return 0;
}
