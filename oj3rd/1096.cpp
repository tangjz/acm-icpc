#include <cstdio>
#include <cstring>
const int maxn = 1010;
typedef long long LL;
LL n, m, h[maxn][maxn], top, hh[maxn], no[maxn], sum, ans;
char str[maxn][maxn];
int main()
{
	while(scanf("%lld%lld", &n, &m) == 2)
	{
		for(LL i = 1; i <= n; ++i)
			scanf("%s", str[i] + 1);
		for(LL j = 1; j <= m; ++j)
			for(LL i = 1; i <= n; ++i)
				h[i][j] = str[i][j] == str[i - 1][j] ? h[i - 1][j] + 1 : 1;
		ans = n * (n + 1) / 2 * m * (m + 1) / 2;
		for(LL i = 1; i <= n; ++i)
			for(LL j = 1; j <= m; ++j)
			{
				if(str[i][j] != str[i][j - 1])
				{
					top = 0;
					no[top] = j - 1;
					sum = 0;
				}
				while(top > 0 && h[i][j] <= hh[top])
				{
					sum -= hh[top] * (no[top] - no[top - 1]);
					--top;
				}
				hh[++top] = h[i][j];
				no[top] = j;
				sum += hh[top] * (no[top] - no[top - 1]);
				ans -= sum;
			}
		printf("%lld\n", ans);
	}
	return 0;
}
