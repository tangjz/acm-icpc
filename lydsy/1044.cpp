#include <cstdio>
const int maxn = 50010, mod = 10007;
int n, m, a[maxn], ans1, f[maxn], ans2;
bool check(int lim)
{
	int ret = 0;
	for(int i = 1, j = 0; i <= n; ++i)
		if(a[i] - a[j] > lim)
		{
			j = i - 1;
			++ret;
		}
	return ret <= m;
}
int main()
{
	int L = 0, R, M;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", a + i);
		if(L < a[i])
			L = a[i];
		a[i] += a[i - 1];
	}
	R = a[n];
	while(L < R)
	{
		M = L + R >> 1;
		if(check(M))
			R = M;
		else
			L = M + 1;
	}
	ans1 = L;
	f[0] = 1;
	for(int i = 0; i <= m; ++i)
	{
		for(int j = n, k = n, g = 0; j; --j)
		{
			while(k >= 0 && a[j] - a[k] <= ans1)
			{
				g += f[k--];
				if(g >= mod)
					g -= mod;
			}
			g -= f[j];
			if(g < 0)
				g += mod;
			f[j] = g;
		}
		f[0] = 0;
		ans2 += f[n];
		if(ans2 >= mod)
			ans2 -= mod;
	}
	printf("%d %d\n", ans1, ans2);
	return 0;
}
