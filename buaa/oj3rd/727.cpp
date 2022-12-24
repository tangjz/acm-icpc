#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 131072;
int t, n, a[maxn], l[maxn], r[maxn], seg[(maxn << 1) + 233], ans;
struct Node
{
	int val, id;
	bool operator < (const Node &x) const
	{
		return val < x.val;
	}
} b[maxn];
void update(int o, int L, int R, int i, int val)
{
	seg[o] = max(seg[o], val);
	if(L == R)
		return;
	int M = L + R >> 1;
	if(i <= M)
		update(o + o, L, M, i, val);
	else
		update(o + o + 1, M + 1, R, i, val);
}
int query(int o, int L, int R, int l, int r)
{
	if(l == L && r == R)
		return seg[o];
	int M = L + R >> 1;
	if(r <= M)
		return query(o + o, L, M, l, r);
	if(l > M)
		return query(o + o + 1, M + 1, R, l, r);
	return max(query(o + o, L, M, l, M), query(o + o + 1, M + 1, R, M + 1, r));
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		memset(seg, 0, sizeof seg);
		scanf("%d", &n);
		b[0] = (Node){-1, 0};
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d", a + i);
			b[i] = (Node){a[i], i};
		}
		sort(b + 1, b + n + 1);
		for(int i = 1, j = 0; i <= n; ++i)
			a[b[i].id] = b[i - 1].val == b[i].val ? j : ++j;
		l[1] = 1;
		for(int i = 2; i <= n; ++i)// i - l[i], i
			l[i] = a[i - 1] < a[i] ? l[i - 1] + 1 : 1;
		r[n] = 1;
		for(int i = n - 1; i; --i)// i, i + r[i]
			r[i] = a[i] < a[i + 1] ? r[i + 1] + 1 : 1;
		ans = 0;
		for(int i = 1; i <= n; ++i)
		{
			if(a[i] > 1)
				ans = max(ans, r[i] + query(1, 1, n, 1, a[i] - 1));
			else
				ans = max(ans, r[i]);
			update(1, 1, n, a[i], l[i]);
		}
		printf("%d\n", ans);
	}
	return 0;
}
