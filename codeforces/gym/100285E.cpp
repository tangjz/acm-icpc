#include <cmath>
#include <cstdio>
const int maxn = 210;
int n, m;
double f[maxn][maxn], fact[maxn];
double calc(int a, int b, int c, int d)
{
	double ret = 0;
	ret += fact[a] - fact[b] - fact[a - b];
	ret += fact[c] - fact[d] - fact[c - d];
	ret -= fact[a + c] - fact[b + d] - fact[a + c - b - d];
	return exp(ret);
}
int main()
{
	for(int i = 2; i < maxn; ++i)
		fact[i] = fact[i - 1] + log(i);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
		for(int j = 0; j <= m && j <= i; ++j)
		{
			if(j == 0)
			{
				f[i][j] = i;
				continue;
			}
			if(j * 2 >= i)
				continue;
			for(int t = 1; t <= i - j; ++t)
			{
				double tmp = 0;
				for(int k = 0; k <= j && k <= t; ++k)
					tmp += f[i - j - t][j - k] * calc(i - j * 2, t - k, j, k);
				if(f[i][j] < tmp)
					f[i][j] = tmp;
			}
		}
	printf("%.8f\n", f[n][m]);
	return 0;
}
