#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100010;
int n, m, q, tot, seg[maxn << 1];
long long s[maxn], ans;
struct Node
{
	int p, x, v;
	bool operator < (const Node &t) const
	{
		return p < t.p || p == t.p && v < t.v;
	}
} que[maxn << 1];
inline int seg_idx(int L, int R)
{
	return L + R | L != R;
}
void update(int L, int R, int x, int v)
{
	while(L < R)
	{
		int M = L + R >> 1;
		seg[seg_idx(L, R)] += v;
		if(x <= M)
			R = M;
		else
			L = M + 1;
	}
	seg[seg_idx(L, R)] += v;
}
int query(int L, int R, int m)
{
	while(L < R)
	{
		int M = L + R >> 1;
		if(seg[seg_idx(L, M)] < m)
		{
			m -= seg[seg_idx(L, M)];
			L = M + 1;
		}
		else
			R = M;
	}
	return L;
}
int main()
{
	while(scanf("%d%d%d", &n, &m, &q) == 3)
	{
		for(int i = 1; i <= n; ++i)
		{
			scanf("%I64d", s + i);
			s[i] += s[i - 1];
		}
		tot = 0;
		while(q--)
		{
			int l, r;
			scanf("%d%d", &l, &r);
			que[tot++] = (Node){l, l, 1};
			que[tot++] = (Node){r + 1, l, -1};
		}
		sort(que, que + tot);
		memset(seg, 0, (n + 1 << 1) * sizeof(int));
		ans = 0;
		for(int i = 1, j = 0; i <= n; ++i)
		{
			for( ; j < tot && que[j].p == i; ++j)
				update(1, n, que[j].x, que[j].v);
			if(seg[seg_idx(1, n)] >= m)
				ans = max(ans, s[i] - s[query(1, n, m) - 1]);
		}
		printf("%I64d\n", ans);
	}
	return 0;
}
