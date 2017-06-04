#include <stdio.h>
const int maxn = 201, maxs = 8120601;
int t, n, m, a[maxn], c[maxn], pos[maxn], pre[maxn];
int Case, tim[maxs], f[maxs];
inline int sqr(int x)
{
	return x * x;
}
inline bool upd(int &x, int y)
{
	return x < y ? (x = y), 1 : 0;
}
inline int idx(int L, int R, int x)
{
	return (L * m + R) * n + x;
}
int F(int L, int R, int x)
{
	if(L > R) // && x == 0
		return 0;
	int id = idx(L, R, x);
	if(tim[id] == Case)
		return f[id];
	tim[id] = Case;
	int ret = F(L, R - 1, 0) + sqr(c[R] + x);
	for(int M = pre[R]; M >= L; M = pre[M])
		if(upd(ret, F(L, M, c[R] + x) + F(M + 1, R - 1, 0)))
			break;
	return f[id] = ret;
}
int main()
{
	scanf("%d", &t);
	for(Case = 1; Case <= t; ++Case)
	{
		m = 0;
		scanf("%d", &n);
		for(int i = 1, x; i <= n; ++i)
		{
			scanf("%d", &x);
			if(m && a[m - 1] == x)
				++c[m - 1];
			else
			{
				a[m] = x;
				c[m++] = 1;
			}
			pos[i] = -1;
		}
		for(int i = 0; i < m; ++i)
		{
			pre[i] = pos[a[i]];
			pos[a[i]] = i;
		}
		++n;
		printf("Case %d: %d\n", Case, F(0, m - 1, 0));
	}
	return 0;
}
