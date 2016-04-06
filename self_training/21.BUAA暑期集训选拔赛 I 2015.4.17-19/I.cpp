#include <cstdio>
const int maxn = 21;
int t, tt, n;
long long c[maxn][maxn], f[maxn];
int main()
{
	for(int i = 0; i < maxn; ++i)
	{
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; ++j)
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
	}
	f[0] = f[1] = 2;
	for(int i = 2; i < maxn; ++i)
		for(int j = 0; j < i; ++j)
			f[i] += c[i - 1][j] * f[j] * f[i - 1 - j] >> 2;
	f[1] = 1;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &tt, &n);
		printf("%d %lld\n", tt, f[n]);
	}
	return 0;
}
