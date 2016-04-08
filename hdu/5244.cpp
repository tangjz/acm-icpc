#include <cstdio>
const int maxn = 1 << 21;
int t, n;
long long a[maxn], b[maxn], c[maxn];
void solve(int x1, int x2, int y1, int y2, long long* c)
{
	if(x1 == x2)
	{
		c[x1] = a[y1];
		return;
	}
	int d = x2 - x1 + 1 >> 1;
	int xm = x1 + d, ym = y1 + d;
	solve(x1, xm - 1, y1, ym - 1, c);
	solve(x1, xm - 1, ym, y2, c + d);
	for(int i = 0; i < d; ++i)
	{
		b[x1 + i] = c[i] + c[d + i];
		b[xm + i] = -c[i] + c[d + i];
	}
	for(int i = 0; i < d << 1; ++i)
		c[i] = b[x1 + i];
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d", &n);
		n = 1 << n;
		for(int i = 0; i < n; ++i)
			scanf("%lld", a + i);
		printf("Case #%d:", Case);
		if(n == 1)
		{
			printf(" %d\n", a[0]);
			continue;
		}
		solve(0, n - 1, 0, n - 1, c);
		c[0] -= (n >> 1) * a[n - 1];
		for(int i = 0; i < n; ++i)
			printf(" %lld", c[i] / (n >> 1));
		putchar('\n');
	}
	return 0;
}
