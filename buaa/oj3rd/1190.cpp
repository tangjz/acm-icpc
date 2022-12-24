#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1024;
const long long INF = 0x3f3f3f3f3f3f3f3fLL;
struct Segment
{
	int cnt;
	long long sum[5];
} seg[maxn << 1];
int n, tot, typ[maxn];
long long que[maxn], val[maxn];
void upd(int o, int l, int r, int p, int f)
{
	if(l == r)
	{
		if(f == 1)
			seg[o].sum[(seg[o].cnt++) % 5] += que[p];
		else
			seg[o].sum[(--seg[o].cnt) % 5] -= que[p];
		return;
	}
	int m = l + r >> 1;
	if(p <= m)
		upd(o + o, l, m, p, f);
	else
		upd(o + o + 1, m + 1, r, p, f);
	seg[o].cnt = seg[o + o].cnt + seg[o + o + 1].cnt;
	for(int i = 0; i < 5; ++i)
		seg[o].sum[i] = seg[o + o].sum[i] + seg[o + o + 1].sum[((i - seg[o + o].cnt) % 5 + 5) % 5];
}
int main()
{
	while(scanf("%d", &n) == 1)
	{
		tot = 0;
		memset(seg, 0, sizeof seg);
		for(int i = 0; i < n; ++i)
		{
			char op[10];
			scanf("%s", op);
			if(op[0] == 's')
				typ[i] = 0;
			else
			{
				typ[i] = op[0] == 'a' ? 1 : -1;
				scanf("%lld", &val[i]);
				que[++tot] = val[i];
			}
		}
		sort(que + 1, que + tot + 1);
		tot = unique(que + 1, que + tot + 1) - que - 1;
		for(int i = 0; i < n; ++i)
			if(typ[i] != 0)
				upd(1, 1, tot, lower_bound(que + 1, que + tot + 1, val[i]) - que, typ[i]);
			else
				printf("%lld\n", seg[1].sum[2]);
	}
	return 0;
}
