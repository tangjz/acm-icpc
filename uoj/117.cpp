#include <cstdio>
#include <cstring>
const int maxn = 100010, maxm = 200010;
int t, n, m, u[maxm], v[maxm], deg[maxn], tot, p[maxn], ans[maxm];
struct Node
{
	int pre, nxt, v, id;
} e[maxm << 1];
void del(int u, int it)
{
	if(e[it].pre == -1)
		p[u] = e[it].nxt;
	else
		e[e[it].pre].nxt = e[it].nxt;
	if(e[it].nxt != -1)
		e[e[it].nxt].pre = e[it].pre;
}
void add(int id)
{
	e[p[u[id]]].pre = tot;
	e[tot] = (Node){-1, p[u[id]], v[id], id};
	p[u[id]] = tot++;
	if(t == 1)
	{
		e[p[v[id]]].pre = tot;
		e[tot] = (Node){-1, p[v[id]], u[id], -id};
		p[v[id]] = tot++;
	}
}
void swap(int &x, int &y)
{
	int t = x;
	x = y;
	y = t;
}
void dfs(int now, int pre)
{
	for(int it = p[now]; it != -1; it = p[now])
	{
		int nxt = e[it].v;
		del(now, it);
		if(t == 1)
			del(nxt, it ^ 1);
		dfs(nxt, it);
	}
	ans[++ans[0]] = pre;
}
int main()
{
	scanf("%d%d%d", &t, &n, &m);
	memset(p, -1, sizeof p);
	for(int i = 1; i <= m; ++i)
	{
		scanf("%d%d", u + i, v + i);
		++deg[u[i]];
		if(t == 1)
			++deg[v[i]];
		else
			--deg[v[i]];
		add(i);
	}
	bool flag = 1;
	for(int i = 1; i <= n; ++i)
		if(t == 1 && (deg[i] & 1) || t == 2 && deg[i])
		{
			flag = 0;
			break;
		}
	if(!flag)
	{
		puts("NO");
		return 0;
	}
	dfs(u[1], -1);
	if(ans[0] != m + 1)
	{
		puts("NO");
		return 0;
	}
	puts("YES");
	for(int i = m; i >= 1; --i)
		printf("%d%c", e[ans[i]].id, " \n"[i == 1]);
	return 0;
}
