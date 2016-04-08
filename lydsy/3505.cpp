#include <cstdio>
const int maxn = 1002;
int res[maxn][maxn], n, m;
long long ans;
long long f(int x)
{
	return x * (x - 1LL) * (x - 2) / 6;
}
int main()
{
	for(int i = 1; i < maxn; ++i)
		res[0][i] = i;
	for(int i = 1; i < maxn; ++i)
		for(int j = i; j < maxn; ++j)
			res[i][j] = res[j % i][i];
	scanf("%d%d", &n, &m);
	++n, ++m;
	ans = f(n * m) - n * f(m) - f(n) * m;
	for(int i = 1; i < n; ++i)
		for(int j = 1; j < m; ++j)
		{
			int tmp = (i < j ? res[i][j] : res[j][i]) - 1;
			ans -= tmp * 2LL * (n - i) * (m - j);
		}
	printf("%lld\n", ans);
	return 0;
}
