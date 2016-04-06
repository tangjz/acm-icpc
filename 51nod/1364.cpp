#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 131072;
int n, m, a[maxn], p[maxn], seg[maxn << 2], cnt[maxn << 2], ans[maxn];
void build(int o, int L, int R)
{
	if(L == R)
	{
		seg[o] = a[L];
		cnt[o] = 1;
		return;
	}
	int M = L + R >> 1;
	build(o + o, L, M);
	build(o + o + 1, M + 1, R);
	seg[o] = max(seg[o + o], seg[o + o + 1]);
	cnt[o] = cnt[o + o] + cnt[o + o + 1];
}
void update(int o, int L, int R, int x)
{
	if(L == R)
	{
		seg[o] = 0;
		cnt[o] = 0;
		return;
	}
	int M = L + R >> 1;
	if(x <= M)
		update(o + o, L, M, x);
	else
		update(o + o + 1, M + 1, R, x);
	seg[o] = max(seg[o + o], seg[o + o + 1]);
	cnt[o] = cnt[o + o] + cnt[o + o + 1];
}
int query(int o, int L, int R, int v)
{
	if(v == cnt[o])
		return seg[o];
	int M = L + R >> 1;
	if(v <= cnt[o + o])
		return query(o + o, L, M, v);
	return max(seg[o + o], query(o + o + 1, M + 1, R, v - cnt[o + o]));
}
int count(int o, int L, int R, int l, int r)
{
	if(L == l && r == R)
		return cnt[o];
	int M = L + R >> 1;
	if(r <= M)
		return count(o + o, L, M, l, r);
	if(l > M)
		return count(o + o + 1, M + 1, R, l, r);
	return count(o + o, L, M, l, M) + count(o + o + 1, M + 1, R, M + 1, r);
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", a + i);
		p[a[i]] = i;
	}
	build(1, 1, n);
	for(int i = 1; i <= n; ++i)
	{
		int x = query(1, 1, n, min(cnt[1], m + 1));
		int pos = p[x];
		ans[i] = x;
		m -= count(1, 1, n, 1, pos) - 1;
		update(1, 1, n, pos);
	}
	for(int i = 1; i <= n; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
