#include <cstdio>
typedef long long LL;
const int maxn = 1001;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
int n, m, x[maxn], cw[maxn], quex[maxn], L, R;
LL sw[maxn], f[maxn][maxn], quey[maxn];
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d%d", x + i, cw + i);
			sw[i] = sw[i - 1] + (LL)x[i] * cw[i];
			cw[i] += cw[i - 1];
		}
		for(int i = 1; i <= m; ++i)
		{
			L = R = 0;
			quex[R] = cw[i - 1];
			quey[R++] = f[i - 1][i - 1] + sw[i - 1];
			for(int j = i; j <= n; ++j)
			{
				while(L + 1 < R && (quey[L + 1] - quey[L]) <= (LL)x[j] * (quex[L + 1] - quex[L]))
					++L;
				f[i][j] = quey[L] - sw[j] + (LL)x[j] * (cw[j] - quex[L]);
				while(L + 1 < R && (quey[R - 1] - quey[R - 2]) * (cw[j] - quex[R - 1]) >= ((f[i - 1][j] + sw[j]) - quey[R - 1]) * (quex[R - 1] - quex[R - 2]))
					--R;
				quex[R] = cw[j];
				quey[R++] = (i > 1 ? f[i - 1][j] : INF) + sw[j];
			}
		}
		printf("%lld\n", f[m][n]);
	}
	return 0;
}
