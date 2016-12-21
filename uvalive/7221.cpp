#include <stdio.h>
#include <algorithm>
typedef long long LL;
const int maxn = 101, maxm = 501;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
int t, n, m, A, B, a[maxn], b[maxm], s[maxm];
LL f[maxn][maxm], ans;
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d%d%d%d", &n, &m, &A, &B);
		for(int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		std::sort(a + 1, a + n + 1);
		ans = 0;
		for(int i = 1, y; i <= m; ++i)
		{
			scanf("%d%d", b + i, &y);
			ans += (LL)y * B;
		}
		std::sort(b + 1, b + m + 1);
		for(int i = 1; i <= m; ++i)
			s[i] = s[i - 1] + b[i];
		f[0][0] = 0;
		for(int j = 1; j <= m; ++j)
			f[0][j] = INF;
		for(int i = 1, idx = 0; i <= n; ++i)
		{
			f[i][0] = 0;
			for( ; idx <= m && b[idx] < a[i]; ++idx);
			for(int j = 1; j <= m; ++j)
			{
				f[i][j] = f[i - 1][j];
				for(int k = 0; k < j; ++k)
				{
					int sei = A + (j - k) * B, mid;
					int seiL = k < idx - 1 ? (std::min(j, idx - 1) - k) * B : 0;
					LL sum = (LL)a[i] * A + (LL)(s[j] - s[k]) * B, sumL;
					if(seiL << 1 >= sei) // left
					{
						int tmp = (sei - 1) / (B << 1) + 1;
						mid = b[k + tmp];
						seiL = tmp * B;
						sumL = (LL)(s[k + tmp] - s[k]) * B;
					}
					else if((seiL + A) << 1 >= sei) // middle
					{
						mid = a[i];
						seiL += A;
						sumL = (LL)a[i] * A + (LL)(s[std::min(j, idx - 1)] - s[k]) * B;
					}
					else // right
					{
						int tmp = (sei - (A << 1) - 1) / (B << 1) + 1;
						mid = b[k + tmp];
						seiL = A + tmp * B;
						sumL = (LL)a[i] * A + (LL)(s[k + tmp] - s[k]) * B;
					}
					LL tmp = f[i - 1][k] + sum - (sumL << 1) - (LL)(sei - (seiL << 1)) * mid;
					if(f[i][j] > tmp)
						f[i][j] = tmp;
				}
			}
		}
		ans += f[n][m];
		printf("Case #%d: %lld\n", Case, ans);
	}
	return 0;
}
