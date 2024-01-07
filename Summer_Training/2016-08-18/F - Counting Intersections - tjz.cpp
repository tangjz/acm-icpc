#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100001;
int t, n, tot, tot_x, que[maxn << 1], bit[maxn << 1];
LL ans;
struct Event
{
	int typ, x1, x2, y;
	bool operator < (const Event &t) const
	{
		if(y != t.y)
			return y < t.y;
		return typ > t.typ;
	}
} e[maxn << 1];
void add(int x, int v)
{
	for( ; x <= tot_x; x += x & -x)
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
		tot = tot_x = 0;
		ans = 0;
		scanf("%d", &n);
		while(n--)
		{
			int x1, y1, x2, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			if(x1 > x2)
				swap(x1, x2);
			if(y1 > y2)
				swap(y1, y2);
			if(x1 == x2)
			{
				e[tot++] = (Event){1, x1 - 1, x2, y1};
				e[tot++] = (Event){-1, x1 - 1, x2, y2};
				que[tot_x++] = x1;
			}
			else
			{
				e[tot++] = (Event){0, x1 - 1, x2, y1};
				que[tot_x++] = x1 - 1;
				que[tot_x++] = x2;
			}
		}
		sort(e, e + tot);
		sort(que, que + tot_x);
		tot_x = unique(que, que + tot_x) - que;
		memset(bit + 1, 0, tot_x * sizeof(int));
		for(int i = 0; i < tot; ++i)
			if(!e[i].typ)
			{
				e[i].x1 = lower_bound(que, que + tot_x, e[i].x1) - que + 1;
				e[i].x2 = lower_bound(que, que + tot_x, e[i].x2) - que + 1;
				ans += sum(e[i].x2) - sum(e[i].x1);
			}
			else
			{
				e[i].x2 = lower_bound(que, que + tot_x, e[i].x2) - que + 1;
				add(e[i].x2, e[i].typ);
			}
		printf("%I64d\n", ans);
	}
	return 0;
}
