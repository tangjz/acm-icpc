#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 524288,
antiprime[36] = {1, 2, 4, 6, 12, 24, 36, 48, 60, 120, 180, 240,
360, 720, 840, 1260, 1680, 2520, 5040, 7560, 10080, 15120, 20160, 25200,
27720, 45360, 50400, 55440, 83160, 110880, 166320, 221760, 277200, 332640, 498960, 554400},
anticnt[36] = {1, 2, 3, 4, 6, 8, 9, 10, 12, 16, 18, 20,
24, 30, 32, 36, 40, 48, 60, 64, 72, 80, 84, 90,
96, 100, 108, 120, 128, 144, 160, 168, 180, 192, 200, 216};
int n, m, pos, a[maxn], seg[maxn << 1], ans, cnt, now;
char s[maxn][11];
void build(int o, int l, int r)
{
	if(l == r)
	{
		seg[o] = 1;
		return;
	}
	int m = l + r >> 1;
	build(o + o, l, m);
	build(o + o + 1, m + 1, r);
	seg[o] = seg[o + o] + seg[o + o + 1];
}
void upd(int o, int l, int r, int v)
{
	if(l == r)
	{
		seg[o] = 0;
		--m;
		if(m)
		{
			pos = (pos - (a[l] > 0) + a[l] - 1) % m;
			if(pos < 0)
				pos += m;
			++pos;
		}
		now = l;
		return;
	}
	int m = l + r >> 1;
	if(v <= seg[o + o])
		upd(o + o, l, m, v);
	else
		upd(o + o + 1, m + 1, r, v - seg[o + o]);
	seg[o] = seg[o + o] + seg[o + o + 1];
}
int main()
{
	while(scanf("%d%d", &n, &pos) == 2)
	{
		for(int i = 1; i <= n; ++i)
			scanf("%s%d", s[i], a + i);
		ans = upper_bound(antiprime, antiprime + 36, n) - antiprime - 1;
		cnt = anticnt[ans];
		ans = antiprime[ans];
		build(1, 1, n);
		m = n;
		for(int i = 1; i <= ans; ++i)
			upd(1, 1, n, pos);
		printf("%s %d\n", s[now], cnt);
	}
	return 0;
}
