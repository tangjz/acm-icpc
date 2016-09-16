#include <set>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 200001;
int t, n, m, tot, que[maxn], bit[maxn], ans;
set<int> pp[maxn];
struct Point
{
	int x, y, c;
	bool operator < (const Point &t) const
	{
		return y < t.y;
	}
} p[maxn];
void upd(int &x, int y)
{
	if(x < y)
		x = y;
}
void add(int x, int v)
{
	for( ; x <= tot; x += x & -x)
		bit[x] += v;
}
int sum(int x)
{
	int ret = 0;
	for( ; x > 0; x -= x & -x)
		ret += bit[x];
	return ret;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		tot = ans = 0;
		memset(bit, 0, sizeof bit);
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; ++i)
		{
			scanf("%d%d%d", &p[i].x, &p[i].y, &p[i].c);
			--p[i].c;
			que[tot++] = p[i].x;
		}
		sort(que, que + tot);
		tot = unique(que, que + tot) - que;
		for(int i = 0; i < n; ++i)
			p[i].x = lower_bound(que, que + tot, p[i].x) - que + 1;
		sort(p, p + n);
		for(int i = 0; i < m; ++i)
		{
			pp[i].clear();
			pp[i].insert(0);
			pp[i].insert(tot + 1);
		}
		for(int i = 0, j; i < n; )
		{
			for(j = i; j < n && p[i].y == p[j].y; ++j)
			{
				set<int>::iterator it = pp[p[j].c].lower_bound(p[j].x);
				int R = *it - 1, L = *(--it);
				upd(ans, sum(R) - sum(L));
			}
			for( ; i < j; ++i)
			{
				add(p[i].x, 1);
				pp[p[i].c].insert(p[i].x);
			}
		}
		for(int i = 0; i < m; ++i)
		{
			int last = 0, now;
			for(set<int>::iterator it = ++pp[i].begin(); it != pp[i].end(); ++it)
			{
				now = *it;
				upd(ans, sum(now - 1) - sum(last));
				last = now;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
