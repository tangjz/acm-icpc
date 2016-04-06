#include <cstdio>
#include <cstring>
const int maxn = 6666, maxm = 23333;
struct Edge
{
	int v, nxt;
} e[maxm];
int t, n, m, tot, lnk[maxn], pre[maxn], cnt, bcc[maxn], d[maxn], ans;
bool used[maxm];
int tarjan(int u, int Fa)
{
	int lowu = pre[u] = ++tot;
	for(int it = lnk[u]; it != -1; it = e[it].nxt)
	{
		if(Fa == (it ^ 1))
			continue;
		int &v = e[it].v;
		if(!pre[v])
		{
			int lowv = tarjan(v, it);
			if(lowu > lowv)
				lowu = lowv;
			if(pre[u] < lowv)
				used[it] = used[it ^ 1] = 1;
		}
		else if(lowu > pre[v])
			lowu = pre[v];
	}
	return lowu;
}
void dfs(int u)
{
	bcc[u] = cnt;
	for(int it = lnk[u]; it != -1; it = e[it].nxt)
		if(!used[it] && !bcc[e[it].v])
			dfs(e[it].v);
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		ans = tot = cnt = 0;
		memset(d, 0, sizeof d);
		memset(pre, 0, sizeof pre);
		memset(bcc, 0, sizeof bcc);
		memset(lnk, -1, sizeof lnk);
		memset(used, 0, sizeof used);
		while(m--)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			e[tot] = (Edge){v, lnk[u]};
			lnk[u] = tot++;
			e[tot] = (Edge){u, lnk[v]};
			lnk[v] = tot++;
		}
		tot = 0;
		tarjan(1, -1);
		for(int i = 1; i <= n; ++i)
			if(!bcc[i])
			{
				++cnt;
				dfs(i);
			}
		for(int u = 1; u <= n; ++u)
			for(int it = lnk[u]; it != -1; it = e[it].nxt)
				if(bcc[u] != bcc[e[it].v])
					++d[bcc[u]];
		for(int i = 1; i <= cnt; ++i)
			if(d[i] == 1)
				++ans;
		printf("%d\n", ans + 1 >> 1);
	}
	return 0;
}
