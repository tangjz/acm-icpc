#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 300001, INF = 0x3f3f3f3f;
int n, m, d, lnk[maxn], dis[maxn], pre[maxn], que[maxn], L, R, ans;
struct Edge {
	int nxt, v;
} e[maxn << 1 | 1];
bool vis[maxn];
int main()
{
	scanf("%d%d%d", &n, &m, &d);
	memset(dis + 1, 0x3f, n * sizeof(int));
	while(m--)
	{
		int x;
		scanf("%d", &x);
		if(!dis[x])
			continue;
		dis[x] = 0;
		pre[x] = -1;
		que[R++] = x;
	}
	for(int i = 1; i < n; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[i << 1] = (Edge){lnk[u], v};
		lnk[u] = i << 1;
		e[i << 1 | 1] = (Edge){lnk[v], u};
		lnk[v] = i << 1 | 1;
	}
	while(L < R)
	{
		int u = que[L++];
		bool chk = 0;
		for(int it = lnk[u]; it; it = e[it].nxt)
		{
			int v = e[it].v;
			if(!chk && pre[u] == v)
				chk = 1;
			else if(dis[v] == INF)
			{
				dis[v] = dis[u] + 1;
				pre[v] = u;
				que[R++] = v;
			}
			else if(!vis[it >> 1])
			{
				vis[it >> 1] = 1;
				++ans;
			}
		}
	}
	printf("%d\n", ans);
	for(int i = 1, o = 0; i < n; ++i)
	{
		if(!vis[i])
			continue;
		o ? putchar(' ') : o = 1;
		printf("%d", i);
	}
	putchar('\n');
	return 0;
}
