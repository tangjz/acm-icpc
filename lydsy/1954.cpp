#include <cstdio>
const int maxn = 100001, maxd = 31;
int n, tot, lnk[maxn], que[maxn], dis[maxn], L, R, ans;
bool vis[maxn];
struct Edge
{
	int nxt, v, w;
} e[maxn << 1];
struct Trie
{
	int ch[2];
} p[maxn * maxd];
int query(int x)
{
	int o = 0, ret = 0;
	for(int i = 31; i >= 0; --i)
	{
		int c = (x >> i) & 1;
		if(p[o].ch[!c])
		{
			o = p[o].ch[!c];
			ret |= !c << i;
		}
		else
		{
			o = p[o].ch[c];
			ret |= c << i;
		}
	}
	return ret;
}
int insert(int x)
{
	int o = 0;
	for(int i = 31; i >= 0; --i)
	{
		int c = (x >> i) & 1;
		if(!p[o].ch[c])
			p[o].ch[c] = tot++;
		o = p[o].ch[c];
	}
}
int main()
{
	scanf("%d", &n);
	++tot;
	for(int i = 1; i < n; ++i)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		e[tot] = (Edge){lnk[u], v, w};
		lnk[u] = tot++;
		e[tot] = (Edge){lnk[v], u, w};
		lnk[v] = tot++;
	}
	tot = 1;
	que[R++] = 1;
	insert(0);
	while(L < R)
	{
		int u = que[L++], tmp = query(dis[u]) ^ dis[u];
		if(ans < tmp)
			ans = tmp;
		insert(dis[u]);
		for(int it = lnk[u]; it; it = e[it].nxt)
			if(!vis[e[it].v])
			{
				dis[e[it].v] = dis[u] ^ e[it].w;
				vis[e[it].v] = 1;
				que[R++] = e[it].v;
			}
	}
	printf("%d\n", ans);
	return 0;
}
