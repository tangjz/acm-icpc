#include <cstdio>
const char *out = "-0+";
const int maxn = 131072;
int n, m, a[maxn], seg[maxn << 2];
inline int sgn(int x)
{
	return (x > 0) - (x < 0);
}
void build(int o, int L, int R)
{
	if(L == R)
	{
		scanf("%d", &seg[o]);
		seg[o] = sgn(seg[o]);
		return;
	}
	int M = L + R >> 1;
	build(o + o, L, M);
	build(o + o + 1, M + 1, R);
	seg[o] = seg[o + o] * seg[o + o + 1];
}
void upd(int o, int L, int R, int x, int v)
{
	if(L == R)
	{
		seg[o] = v;
		return;
	}
	int M = L + R >> 1;
	if(x <= M)
		upd(o + o, L, M, x, v);
	else
		upd(o + o + 1, M + 1, R, x, v);
	seg[o] = seg[o + o] * seg[o + o + 1];
}
int que(int o, int L, int R, int l, int r)
{
	if(l == L && r == R)
		return seg[o];
	int M = L + R >> 1;
	if(r <= M)
		return que(o + o, L, M, l, r);
	else if(l > M)
		return que(o + o + 1, M + 1, R, l, r);
	else
		return que(o + o, L, M, l, M) * que(o + o + 1, M + 1, R, M + 1, r);
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		build(1, 1, n);
		for(int i = 0; i < m; ++i)
		{
			int x, y;
			char op[2];
			scanf("%s%d%d", op, &x, &y);
			if(op[0] == 'C')
				upd(1, 1, n, x, sgn(y));
			else
				putchar(out[que(1, 1, n, x, y) + 1]);
		}
		putchar('\n');
	}
	return 0;
}
