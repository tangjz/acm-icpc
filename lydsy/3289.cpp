#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 50001;
int n, q, a[maxn], tot, que[maxn], sqn, bit[maxn], L, R, tmp, ans[maxn];
struct Query
{
	int id, l, r;
	bool operator < (const Query &t) const
	{
		if(l / sqn != t.l / sqn)
			return l < t.l;
		return r < t.r;
	}
} Q[maxn];
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
	scanf("%d", &n);
	sqn = sqrt(n + 0.1);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", a + i);
		que[tot++] = a[i];
	}
	sort(que, que + tot);
	tot = unique(que, que + tot) - que;
	for(int i = 1; i <= n; ++i)
		a[i] = lower_bound(que, que + tot, a[i]) - que + 1;
	scanf("%d", &q);
	for(int i = 0; i < q; ++i)
	{
		Q[i].id = i;
		scanf("%d%d", &Q[i].l, &Q[i].r);
	}
	sort(Q, Q + q);
	L = 1;
	for(int i = 0; i < q; ++i)
	{
		for( ; L < Q[i].l; ++L)
		{
			tmp -= sum(a[L] - 1);
			add(a[L], -1);
		}
		for( ; L > Q[i].l; --L)
		{
			tmp += sum(a[L - 1] - 1);
			add(a[L - 1], 1);
		}
		for( ; R < Q[i].r; ++R)
		{
			tmp += R - L + 1 - sum(a[R + 1]);
			add(a[R + 1], 1);
		}
		for( ; R > Q[i].r; --R)
		{
			tmp -= R - L + 1 - sum(a[R]);
			add(a[R], -1);
		}
		ans[Q[i].id] = tmp;
	}
	for(int i = 0; i < q; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
