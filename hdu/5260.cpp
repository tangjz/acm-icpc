#include <cstdio>
#include <cstring>
const int maxn = 4000, maxs = 500;
int tt, n, m, s, t, tot;
char ans[maxs];
bool g[maxn], vis[maxn], nxt[maxn];
struct Edge
{
	int u, v;
	char w;
} e[maxn];
int main()
{
	scanf("%d", &tt);
	for(int Case = 1; Case <= tt; ++Case)
	{
		printf("Case #%d:\n", Case);
		scanf("%d%d%d%d", &n, &m, &s, &t);
		tot = 0;
		for(int i = 0; i < m; ++i)
		{
			int u, v;
			char str[10];
			scanf("%d%d%s", &u, &v, str);
			for(int j = 0; str[j]; ++j)
			{
				int x = j ? n - 1 : u, y = str[j + 1] ? n++ : v;
				e[tot++] = (Edge){x, y, str[j]};
			}
		}
		memset(g, 0, sizeof g);
		g[t] = 1;
		for(int i = 0; i < n + 10; ++i)
		{
			bool upd = 0;
			for(int j = 0; j < tot; ++j)
				if(!g[e[j].u] && g[e[j].v])
					upd = g[e[j].u] = 1;
			if(!upd)
				break;
		}
		if(!g[s])
		{
			puts("Tough way!");
			continue;
		}
		bool flag = 0;
		memset(vis, 0, sizeof vis);
		memset(ans, 0, sizeof ans);
		vis[s] = 1;
		for(int i = 0; i < maxs; ++i)
		{
			if(vis[t])
			{
				flag = 1;
				break;
			}
			memset(nxt, 0, sizeof nxt);
			char tmp = 'z' + 1;
			for(int j = 0; j < tot; ++j)
				if(vis[e[j].u] && g[e[j].v] && e[j].w <= tmp)
					tmp = e[j].w;
			for(int j = 0; j < tot; ++j)
				if(vis[e[j].u] && g[e[j].v] && e[j].w == tmp)
					nxt[e[j].v] = 1;
			ans[i] = tmp;
			memcpy(vis, nxt, sizeof nxt);
		}
		puts(flag ? ans : "Tough way!");
	}
	return 0;
}
