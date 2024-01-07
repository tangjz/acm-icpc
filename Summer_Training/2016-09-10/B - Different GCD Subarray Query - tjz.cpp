#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100001, maxm = 1000001;
int n, q, a[maxn], tot, tim[maxm], pos[maxm], cnt, bit[maxn], ans[maxn];
pair<int, int> stack[maxn];
struct Query
{
	int idx, l, r;
	bool operator < (const Query &t) const
	{
		return r < t.r;
	}
} query[maxn];
void add(int x, int v)
{
	for( ; x <= n; x += x & -x)
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
	for(int Case = 1; scanf("%d%d", &n, &q) == 2; ++Case)
	{
		tot = cnt = 0;
		memset(bit + 1, 0, n * sizeof(int));
		for(int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		for(int i = 1; i <= q; ++i)
		{
			query[i].idx = i;
			scanf("%d%d", &query[i].l, &query[i].r);
		}
		sort(query + 1, query + q + 1);
		for(int i = 1, o = 1; i <= n; ++i)
		{
			stack[tot++] = make_pair(0, i);
			for(int j = 0; j < tot; ++j)
				stack[j].first = __gcd(stack[j].first, a[i]);
			int tmp = 0;
			for(int j = 0; j < tot; ++j)
				if(!tmp || stack[tmp - 1].first != stack[j].first)
					stack[tmp++] = stack[j];
			tot = tmp;
			for(int j = tot - 1, last = i + 1; j >= 0; last = stack[j--].second)
			{
				int val = stack[j].first, idx = last - 1;
				if(tim[val] == Case)
				{
					add(pos[val], -1);
					pos[val] = idx;
					add(pos[val], 1);
				}
				else
				{
					tim[val] = Case;
					pos[val] = idx;
					add(pos[val], 1);
					++cnt;
				}
			}
			for( ; o <= q && query[o].r == i; ++o)
				ans[query[o].idx] = cnt - sum(query[o].l - 1);
		}
		for(int i = 1; i <= q; ++i)
			printf("%d\n", ans[i]);
	}
	return 0;
}
