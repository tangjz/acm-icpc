#include <cmath>
#include <stdio.h>
#include <algorithm>
const int maxn = 50001;
int n, m, q, a[maxn], tot, que[maxn], sz, lpos[maxn], qL[maxn], qR[maxn], bit[maxn];
long long ans[maxn];
struct Query
{
	int idx, l, r;
	bool operator < (const Query &t) const
	{
		if(lpos[l] != lpos[t.l])
			return lpos[l] < lpos[t.l];
		return r < t.r;
	}
} query[maxn];
void upd(int x, int v)
{
	for( ; x <= tot; x += x & -x)
		bit[x] += v;
}
int calc(int x)
{
	int ret = 0;
	for( ; x > 0; x -= x & -x)
		ret += bit[x];
	return ret;
}
int main()
{
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", a + i);
		que[tot++] = a[i];
	}
	std::sort(que, que + tot);
	tot = std::unique(que, que + tot) - que;
	for(int i = 1; i <= n; ++i)
	{
		qL[i] = std::lower_bound(que, que + tot, a[i] - m) - que;
		qR[i] = std::lower_bound(que, que + tot, a[i] + m + 1) - que;
		a[i] = std::lower_bound(que, que + tot, a[i]) - que + 1;
	}
	for(int i = 0; i < q; ++i)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		query[i] = (Query){i, ++l, ++r};
	}
	sz = (int)ceil(sqrt(n));
	for(int i = 1, j = 1, k = 1; i <= n; ++i, (k == sz ? (++j, k = 1) : ++k))
		lpos[i] = j;
	std::sort(query, query + q);
	long long sum = 0;
	for(int i = 0, L = 1, R = 0; i < q; ++i)
	{
		for( ; R < query[i].r; ++R)
		{
			sum += calc(qR[R + 1]) - calc(qL[R + 1]);
			upd(a[R + 1], 1);
		}
		for( ; L > query[i].l; --L)
		{
			sum += calc(qR[L - 1]) - calc(qL[L - 1]);
			upd(a[L - 1], 1);
		}
		for( ; L < query[i].l; ++L)
		{
			upd(a[L], -1);
			sum -= calc(qR[L]) - calc(qL[L]);
		}
		for( ; R > query[i].r; --R)
		{
			upd(a[R], -1);
			sum -= calc(qR[R]) - calc(qL[R]);
		}
		ans[query[i].idx] = sum;
	}
	for(int i = 0; i < q; ++i)
		printf("%lld\n", ans[i]);
	return 0;
}
