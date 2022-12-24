#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 524288;
int t, n, q[maxn][3], seg[maxn + maxn + 233], lazy[maxn + maxn + 233], tot;
struct Node
{
	int val, id;
	bool operator < (const Node &x) const
	{
		return val < x.val;
	}
} num[maxn << 1];
void update(int o, int L, int R, int l, int r, int val)
{
	seg[o] = max(seg[o], val);
	if(l == L && r == R)
	{
		lazy[o] = max(lazy[o], val);
		return;
	}
	if(L != R && lazy[o])
	{
		seg[o + o] = max(seg[o + o], lazy[o]);
		seg[o + o + 1] = max(seg[o + o + 1], lazy[o]);
		lazy[o + o] = max(lazy[o + o], lazy[o]);
		lazy[o + o + 1] = max(lazy[o + o + 1], lazy[o]);
		lazy[o] = 0;
	}
	int M = L + R >> 1;
	if(r <= M)
		update(o + o, L, M, l, r, val);
	else if(l > M)
		update(o + o + 1, M + 1, R, l, r, val);
	else
	{
		update(o + o, L, M, l, M, val);
		update(o + o + 1, M + 1, R, M + 1, r, val);
	}
}
int query(int o, int L, int R, int x)
{
	if(x == L && x == R)
		return seg[o];
	if(L != R && lazy[o])
	{
		seg[o + o] = max(seg[o + o], lazy[o]);
		seg[o + o + 1] = max(seg[o + o + 1], lazy[o]);
		lazy[o + o] = max(lazy[o + o], lazy[o]);
		lazy[o + o + 1] = max(lazy[o + o + 1], lazy[o]);
		lazy[o] = 0;
	}
	int M = L + R >> 1;
	if(x <= M)
		return query(o + o, L, M, x);
	return query(o + o + 1, M + 1, R, x);
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		memset(seg, 0, sizeof seg);
		for(int i = 0; i < n; ++i)
		{
			scanf("%d%d%d", &q[i][2], &q[i][0], &q[i][1]);
			if(q[i][0] > q[i][1])
				swap(q[i][0], q[i][1]);
			num[i + i] = (Node){q[i][0], i + i};
			num[i + i + 1] = (Node){q[i][1], i + i + 1};
		}
		sort(num, num + n + n);
		q[num[0].id >> 1][num[0].id & 1] = ++tot;
		for(int i = 1, j = 1; i < n + n; ++i)
			q[num[i].id >> 1][num[i].id & 1] = num[i - 1].val == num[i].val ? tot : ++tot;
		for(int i = 0; i < n; ++i)
			if(q[i][2] == 1)
				update(1, 1, tot, q[i][0], q[i][1], q[i][1]);
			else
				puts(query(1, 1, tot, q[i][0]) >= q[i][1] ? "YES" : "NO");
	}
	return 0;
}
