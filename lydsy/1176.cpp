#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 200001, maxm = 10001;
int n, m, tot, que[maxn], t, vis[maxn], bit[maxn], ans[maxm];
struct Oper
{
	int typ, x, y, val;
} p[maxn], q[maxn];
void add(int x, int v)
{
	for( ; x <= tot; x += x & -x)
		if(vis[x] == t)
			bit[x] += v;
		else
		{
			vis[x] = t;
			bit[x] = v;
		}
}
int sum(int x)
{
	int ret = 0;
	for( ; x > 0; x -= x & -x)
		if(vis[x] == t)
			ret += bit[x];
	return ret;
}
void solve(int L, int R)
{
	if(L == R)
		return;
	int M = L + R >> 1, cnt = 0;
	solve(L, M);
	solve(M + 1, R);
	++t;
	for(int i = L, j = M + 1; i <= M || j <= R; )
		if(j > R || i <= M && p[i].x <= p[j].x)
		{
			if(!p[i].typ)
				add(p[i].y, p[i].val);
			q[cnt++] = p[i++];
		}
		else
		{
			if(p[j].typ)
				ans[p[j].val] += p[j].typ * sum(p[j].y);
			q[cnt++] = p[j++];
		}
	for(int i = 0; i < cnt; ++i)
		p[L + i] = q[i];
}
int main()
{
	int typ, a, b, c, d, s;
	scanf("%d%*d", &s);
	while(scanf("%d", &typ) == 1)
		if(typ == 1)
		{
			scanf("%d%d%d", &a, &b, &c);
			p[++n] = (Oper){0, a, b, c};
			que[++tot] = b;
		}
		else if(typ == 2)
		{
			scanf("%d%d%d%d", &a, &b, &c, &d);
			--a, --b, ++m;
			p[++n] = (Oper){1, c, d, m};
			p[++n] = (Oper){-1, a, d, m};
			p[++n] = (Oper){-1, c, b, m};
			p[++n] = (Oper){1, a, b, m};
			que[++tot] = b;
			que[++tot] = d;
			ans[m] = (c - a) * (d - b) * s;
		}
		else
			break;
	sort(que + 1, que + tot + 1);
	tot = unique(que + 1, que + tot + 1) - que - 1;
	for(int i = 1; i <= n; ++i)
		p[i].y = lower_bound(que + 1, que + tot + 1, p[i].y) - que;
	solve(1, n);
	for(int i = 1; i <= m; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
