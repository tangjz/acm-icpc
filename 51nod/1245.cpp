#include <stdio.h>
typedef long long LL;
const int maxn = 61;
int t, len;
LL m, p, dig[maxn], f[maxn][maxn][2];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld%lld", &m, &p);
		for(len = 0; m > 0; dig[++len] = m % p, m /= p);
		f[0][0][0] = 1;
		for(int i = 1; i <= len; ++i)
			for(int j = 0; j <= i; ++j)
			{
				f[i][j][0] = (dig[i] + 1) * f[i - 1][j][0] + (j ? dig[i] * f[i - 1][j - 1][1] : 0);
				f[i][j][1] = (p - 1 - dig[i]) * f[i - 1][j][0] + (j ? (p - dig[i]) * f[i - 1][j - 1][1] : 0);
			}
		for(int i = 0; i < len && f[len][i][0]; ++i)
			printf("%lld ", f[len][i][0]);
		putchar('\n');
	}
	return 0;
}
