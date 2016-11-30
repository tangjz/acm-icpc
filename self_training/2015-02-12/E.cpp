#include <cmath>
#include <cstdio>
#include <cstring>
const int maxn = 202;
int n, a[maxn], s, t, tot, pre[maxn], level[maxn], que[maxn], head, tail, flow, ans, out[maxn][maxn];
struct Edge
{
	int nxt, v, cost;
} e[maxn + maxn * maxn << 1];
bool isprime(int x)
{
	for(int i = 2, j = (int)sqrt(x); i <= j; ++i)
		if(x % i == 0)
			return 0;
	return 1;
}
void addedge(int u, int v, int c)
{
	e[tot] = (Edge){pre[u], v, c};
	pre[u] = tot++;
	e[tot] = (Edge){pre[v], u, 0};
	pre[v] = tot++;
}
bool bfs()
{
	head = tail = 1;
	memset(level, 0, sizeof level);
	level[s] = 1;
	que[tail++] = s;
	while(head < tail)
	{
		int u = que[head++];
		for(int it = pre[u]; it != -1; it = e[it].nxt)
			if(e[it].cost && !level[e[it].v])
			{
				level[e[it].v] = level[u] + 1;
				que[tail++] = e[it].v;
			}
	}
	return level[t];
}
int min(int x, int y)
{
	return x < y ? x : y;
}
int dfs(int u, int lim)
{
	if(u == t || !lim)
		return lim;
	int flow = 0, tmp;
	for(int it = pre[u]; it != -1; it = e[it].nxt)
		if(level[e[it].v] == level[u] + 1 && e[it].cost && (tmp = dfs(e[it].v, min(e[it].cost, lim - flow))))
		{
			e[it].cost -= tmp;
			e[it ^ 1].cost += tmp;
			flow += tmp;
		}
	return flow;
}
void print(int now, int flag)
{
	level[now] = 1;
	out[ans][++out[ans][0]] = now;
	if(!flag)
		for(int it = pre[now]; it != -1; it = e[it].nxt)
			if(e[it].v != s && !level[e[it].v] && !e[it].cost)
			{
				print(e[it].v, flag ^ 1);
				return;
			}
	if(flag)
		for(int it = pre[now]; it != -1; it = e[it].nxt)
			if(e[it].v != t && !level[e[it].v] && e[it].cost)
			{
				print(e[it].v, flag ^ 1);
				return;
			}
}
int main()
{
	scanf("%d", &n);
	s = 0, t = n + 1;
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	memset(pre, -1, sizeof pre);
	for(int i = 1; i <= n; ++i)
		if(a[i] & 1)
			addedge(s, i, 2);
		else
			addedge(i, t, 2);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			if((a[i] & 1) && !(a[j] & 1) && isprime(a[i] + a[j]))
				addedge(i, j, 1);
	while(bfs())
	{
		int tmp;
		while((tmp = dfs(s, 0x3f3f3f3f)))
			flow += tmp;
	}
	if(flow != n)
	{
		puts("Impossible");
		return 0;
	}
	memset(level, 0, sizeof level);
	for(int i = 1; i <= n; ++i)
		if((a[i] & 1) && !level[i])
		{
			print(i, 0);
			++ans;
		}
	printf("%d\n", ans);
	for(int i = 0; i < ans; ++i)
		for(int j = 0; j <= out[i][0]; ++j)
			printf("%d%c", out[i][j], " \n"[j == out[i][0]]);
	return 0;
}
