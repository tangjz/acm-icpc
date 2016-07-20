#include <cstdio>
#include <algorithm>
typedef long long LL;
const int maxn = 1001;
int t, n, m, U[maxn][maxn], c[maxn][maxn], f[maxn][maxn], tot, quex[maxn], quey[maxn];
LL sum;
char str[maxn][maxn + 1];
void solve()
{
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			if(str[i][j] != 'G')
				U[i][j] = U[i - 1][j];
			else
			{
				int delta = i - U[i - 1][j] - 1;
				sum += 4LL * delta * f[U[i - 1][j]][j];
				c[i][j] = c[U[i - 1][j]][j] + delta;
				U[i][j] = i;
				f[i][j] = c[i][j];
				for(int k = j - 1, o = k ? U[i - 1][k] : 0; o > 0; o = k > 1 ? U[o - 1][--k] : 0)
					f[i][j] += c[o][k];
				for(int k = j + 1, o = k <= m ? U[i - 1][k] : 0; o > 0; o = k < m ? U[o - 1][++k] : 0)
					f[i][j] += c[o][k];
			}
	for(int i = 1; i <= m; ++i)
		sum += 4LL * (n - U[n][i]) * f[U[n][i]][i];
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		tot = 0;
		scanf("%d%d", &n, &m);
		sum = 0;
		// add any to any
		for(int i = 1; i < n; ++i)
			sum += 2LL * i * (n - i) * m * m;
		for(int i = 1; i < m; ++i)
			sum += 2LL * n * n * i * (m - i);
		for(int i = 1; i <= n; ++i)
		{
			scanf("%s", str[i] + 1);
			for(int j = 1; j <= m; ++j)
				if(str[i][j] == 'G')
				{
					quex[tot] = i;
					quey[tot++] = j;
					// sub guard to any
					for(int k = 1; k <= n; ++k)
						sum -= abs(i - k) * m << 1;
					for(int k = 1; k <= m; ++k)
						sum -= n * abs(j - k) << 1;
				}
		}
		// add guard to guard
		for(int i = 0; i < tot; ++i)
			for(int j = i + 1; j < tot; ++j)
				sum += (abs(quex[i] - quex[j]) + abs(quey[i] - quey[j])) << 1;
		solve();
		{
			int mx = std::max(n, m);
			for(int i = 1; i <= mx; ++i)
				for(int j = i + 1; j <= mx; ++j)
					std::swap(str[i][j], str[j][i]);
			std::swap(n, m);
		}
		solve();
		printf("%.4f\n", (double)sum / ((LL)(n * m - tot) * (n * m - tot)));
	}
	return 0;
}
