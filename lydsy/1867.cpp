/*
 * 计算方案数，总体方案数为2^n
 */
#include <cstdio>
const int maxn = 51;
int n, m;
long long f[maxn][maxn], sum;
char c;
int main()
{
	scanf("%d%d", &n, &m);
	f[0][0] = 1;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j <= i; ++j)
		{
			while((c = getchar()) != '*' && c != '.');
			if(c == '*')
			{
				f[i + 1][j] += f[i][j];
				f[i + 1][j + 1] += f[i][j];
			}
			else f[i + 2][j + 1] += f[i][j] << 2;
		}
	sum = 1ll << n;
	while(!(f[n][m] & 1))
	{
		f[n][m] >>= 1;
		sum >>= 1;
	}
	printf("%lld/%lld\n", f[n][m], sum);
	return 0;
}
