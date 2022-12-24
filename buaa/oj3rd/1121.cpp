#include <cstdio>
int n, a[233], f[233][233];
int min(int x, int y)
{
	return x < y ? x : y;
}
int main()
{
	while(scanf("%d", &n) == 1)
	{
		a[n + 1] = 0;
		for(int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		for(int i = 1; i <= n; ++i)
			f[i][i] = a[i - 1] + a[i + 1];
		for(int i = 2; i <= n; ++i)
			for(int l = 1; l <= n; ++l)
			{
				int r = l + i - 1;
				if(r > n)
					break;
				f[l][r] = min(f[l + 1][r], f[l][r - 1]);
				for(int k = l + 1; k < r; ++k)
					f[l][r] = min(f[l][r], f[l][k - 1] + f[k + 1][r]);
				f[l][r] += a[l - 1] + a[r + 1];
			}
		printf("%d\n", f[1][n]);
	}
	return 0;
}
