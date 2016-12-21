#include <cmath>
#include <stdio.h>
#include <algorithm>
typedef double DB;
const int maxn = 10001, maxm = 11;
const DB INF = 1e10;
int t, n, m, ord[maxm], p[maxm][maxn], pL, pR, pC, out[maxm];
DB a[maxn], b[maxm], f[maxm][maxn], ans;
inline DB getValue()
{
	static int x, y;
	scanf("%d/%d", &x, &y);
	return log((DB)x) - log((DB)y);
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i)
			a[i] = getValue();
		for(int i = 1; i <= m; ++i)
		{
			b[i] = getValue();
			ord[i] = i;
			out[i] = 0;
		}
		std::sort(ord + 1, ord + m + 1, [](const int &x, const int &y) {
			return b[x] > b[y];
		});
		ans = -INF;
		for(int i = 0; i <= m; ++i)
		{
			f[i][0] = i ? -INF : 0;
			for(int j = 1; j <= n; ++j)
			{
				f[i][j] = -INF;
				if(!i && f[i][j] < a[j])
				{
					f[i][j] = a[j];
					p[i][j] = -1;
				}
				if(i == 1 && f[i][j] < b[ord[i]])
				{
					f[i][j] = b[ord[i]];
					p[i][j] = -2;
				}
				if(f[i][j] < f[i][j - 1] + a[j])
				{
					f[i][j] = f[i][j - 1] + a[j];
					p[i][j] = 1;
				}
				if(i && f[i][j] < f[i - 1][j - 1] + b[ord[i]])
				{
					f[i][j] = f[i - 1][j - 1] + b[ord[i]];
					p[i][j] = 2;
				}
				if(ans < f[i][j])
				{
					ans = f[i][j];
					pC = i;
					pR = j;
				}
			}
		}
		pL = pR;
		while(1)
		{
			int d = std::abs(p[pC][pL]);
			if(d > 1)
				out[ord[pC]] = pL;
			if(p[pC][pL] < 0)
				break;
			if(d > 1)
				--pC;
			--pL;
		}
		printf("Case #%d:\n%d %d\n", Case, pL, pR);
		for(int i = 1; i <= m; ++i)
			printf("%d%c", out[i], " \n"[i == m]);
	}
	return 0;
}
