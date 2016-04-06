#include <cstdio>
int n, m, dx, dy, f[2333333], cnt[2333333], ans[3];
int main()
{
	scanf("%d%d%d%d", &n, &m, &dx, &dy);
	for(int i = 0, x = 0, y = 0; i < n; ++i)
	{
		f[x] = y;
		x += dx;
		if(x >= n)
			x -= n;
		y += dy;
		if(y >= n)
			y -= n;
	}
	for(int x, y; m; --m)
	{
		scanf("%d%d", &x, &y);
		y -= f[x];
		if(y < 0)
			y += n;
		++cnt[y];
		if(ans[0] < cnt[y])
		{
			ans[0] = cnt[y];
			ans[1] = x;
			ans[2] = y + f[x];
			if(ans[2] >= n)
				ans[2] -= n;
		}
	}
	printf("%d %d\n", ans[1], ans[2]);
	return 0;
}
