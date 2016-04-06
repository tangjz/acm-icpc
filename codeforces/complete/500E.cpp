#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 233333;
int n, q, l[maxn], r[maxn], fa[maxn], que[maxn], head, tail;
long long sum[maxn], ans[maxn];
struct Node
{
	int x, y, id;
	bool operator < (const Node &t) const
	{
		return x > t.x;
	}
} query[maxn];
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d%d", l + i, r + i);
		r[i] += l[i];
		fa[i] = i;
	}
	scanf("%d", &q);
	for(int i = 0; i < q; ++i)
	{
		scanf("%d%d", &query[i].x, &query[i].y);
		query[i].id = i;
	}
	sort(query, query + q);
	head = 0, tail = -1;
	for(int i = n, j = 0; i; --i)
	{
		while(head <= tail && l[que[tail]] <= r[i])
		{
			if(r[i] < r[que[tail]])
				r[i] = r[que[tail]];
			fa[find(que[tail])] = i;
			--tail;
		}
		if(head <= tail)
			sum[i] = sum[que[tail]] + l[que[tail]] - r[i];
		while(j < q && query[j].x == i)
		{
			ans[query[j].id] = sum[i] - sum[find(query[j].y)];
			++j;
		}
		que[++tail] = i;
	}
	for(int i = 0; i < q; ++i)
		printf("%I64d\n", ans[i]);
	return 0;
}
