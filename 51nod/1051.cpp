#include <stdio.h>
typedef long long LL;
const int maxn = 501;
int n, m, x;
LL s[maxn][maxn], ans;
int main()
{
	scanf("%d%d", &m, &n);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
		{
			scanf("%d", &x);
			s[i][j] = x + s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
		}
	for(int L = 1; L <= n; ++L)
		for(int R = L; R <= n; ++R)
		{
			LL tmp = 0;
			for(int i = 1; i <= m; ++i)
			{
				LL val = s[R][i] - s[L - 1][i];
				if(ans < val - tmp)
					ans = val - tmp;
				if(tmp > val)
					tmp = val;
			}
		}
	printf("%lld\n", ans);
	return 0;
}
