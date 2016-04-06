#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 131072;
struct Segment
{
	int cnt;
	long long sum[5];
} seg[maxn << 1];
int n, tot, que[maxn], typ[maxn], val[maxn];
void upd(int o, int l, int r, int p, int f)
{
	if(l == r)
	{
		seg[o].cnt += f;
		seg[o].sum[1] += que[p] * f;
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
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		char op[5];
		scanf("%s", op);
		if(op[0] != 's')
		{
			typ[i] = op[0] == 'a' ? 1 : -1;
			scanf("%d", val + i);
			que[++tot] = val[i];
		}
	}
	sort(que + 1, que + tot + 1);
	tot = unique(que + 1, que + tot + 1) - que - 1;
	for(int i = 0; i < n; ++i)
		if(typ[i])
		{
			val[i] = lower_bound(que + 1, que + tot + 1, val[i]) - que;
			upd(1, 1, tot, val[i], typ[i]);
		}
		else
			printf("%I64d\n", seg[1].sum[3]);
	return 0;
}
