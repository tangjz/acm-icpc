#include <cstdio>
#include <cstring>
const int maxs = 1 << 15, mod = 1000000000;
int t, n, m, x, f[maxs], ans;
void inc(int &x, int y)
{
	x += y;
	if(x >= mod)
		x -= mod;
}
void swap(int &x, int &y)
{
	int t = x;
	x = y;
	y = t;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		memset(f, 0, (1 << m) * sizeof(int));
		f[0] = 1;
		while(n--)
		{
			scanf("%d", &x);
			for(int i = 0; i < m; ++i)
				for(int j = 0; j < 1 << m - 1; ++j)
					inc(f[((j >> i) << i + 1) | (1 << i) | (j & ((1 << i) - 1))],
						f[((j >> i) << i + 1) | (j & ((1 << i) - 1))]);
			for(int i = 0; i < 1 << m - 1; ++i)
				swap(f[i], f[(1 << m) - 1 - i]);
			for(int i = 0; i < 1 << m; i += x)
				f[i] = 0;
		}
		ans = 0;
		for(int i = 0; i < 1 << m; ++i)
			inc(ans, f[i]);
		printf("%d\n", ans);
	}
	return 0;
}