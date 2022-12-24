#include <cstdio>
#include <cstring>
const int maxn = 100005, maxm = 400005;
int n, m, u[maxm], v[maxm], deg[maxn], dsu[maxn], seq[maxn], tot, p[maxn], ans[maxm];
void swap(int &x, int &y)
{
	int t = x;
	x = y;
	y = t;
}
int dsu_find(int x) {
	return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
}
void dsu_merge(int x, int y) {
	x = dsu_find(x);
	y = dsu_find(y);
	if(x == y)
		return;
	if(dsu[x] < dsu[y])
		swap(x, y);
	if(dsu[x] == dsu[y])
		--dsu[y];
	dsu[x] = y;
}
struct Node
{
	int pre, nxt, v, id;
} e[maxm << 1 | 1];
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
	e[p[v[id]]].pre = tot;
	e[tot] = (Node){-1, p[v[id]], u[id], -id};
	p[v[id]] = tot++;
	dsu_merge(u[id], v[id]);
}
bool dir[maxm];
void dfs(int now, int pre)
{
	for(int it = p[now]; it != -1; it = p[now])
	{
		int nxt = e[it].v;
		del(now, it);
		del(nxt, it ^ 1);
		dfs(nxt, it);
	}
	if(pre != -1)
		dir[pre >> 1] = pre & 1;
	ans[++ans[0]] = pre;
}
int main()
{
	scanf("%d%d", &n, &m);
	memset(p, -1, sizeof p);
	memset(dsu, -1, sizeof dsu);
	for(int i = 1; i <= m; ++i)
	{
		scanf("%d%d", u + i, v + i);
		++deg[u[i]];
		++deg[v[i]];
		add(i);
	}
	int dt = 0, ans = 0;
	for(int i = 1; i <= n; ++i)
		if(deg[i] & 1)
		{
			int fa = dsu_find(i);
			if(seq[fa]) {
				++dt;
				u[m + dt] = seq[fa];
				v[m + dt] = i;
				++deg[seq[fa]];
				++deg[i];
				seq[fa] = 0;
				add(m + dt);
			} else {
				seq[fa] = i;
			}
		}
		else
			++ans;
	for(int i = 1; i <= n; ++i)
		if(p[i] != -1)
			dfs(i, -1);
	printf("%d\n", ans);
	for(int i = 0; i < m; ++i)
		putchar(dir[i] ? '1' : '0');
	return 0;
}
