#include <cstdio>
#include <cstring>
const int maxn = 102;
int n, m, a[maxn][maxn], b[maxn][maxn], sum, ans;
bool check(int r, int c)
{
	memcpy(b, a, sizeof a);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
		{
			if(b[i][j] < 0)
				return 0;
			if(i <= n - r + 1 && j <= m - c + 1)
			{
				b[i + r][j + c] -= b[i][j];
				b[i + r][j] += b[i][j];
				b[i][j + c] += b[i][j];
				b[i][j] = 0;
			}
			if(b[i][j] > 0)
				return 0;
		}
	return 1;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
		{
			scanf("%d", &a[i][j]);
			sum += a[i][j];
		}
	for(int i = n; i; --i)
		for(int j = m; j; --j)
			a[i][j] -= a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
	ans = sum;
	for(int r = n; r; --r)
		for(int c = m; c; --c)
			if(sum % (r * c) == 0 && ans > sum / r / c && check(r, c))
				ans = sum / r / c;
	printf("%d\n", ans);
	return 0;
}
