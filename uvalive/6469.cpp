#include <cstdio>
const int maxn = 18;
typedef long long LL;
int t, id, n, m;
LL fact[maxn], c[maxn][maxn], ans;
int main()
{
	fact[0] = c[0][0] = 1;
	for(int i = 1; i < maxn; ++i)
	{
		fact[i] = fact[i - 1] * i;
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; ++j)
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
	}
	scanf("%d", &t);
	while(t--)
	{
		ans = 0;
		scanf("%d%d%d", &id, &n, &m);
		for(int i = 0; i <= m; ++i)
			ans += (i & 1 ? -1 : 1) * c[m][i] * fact[n - i];
		printf("%d %lld\n", id, ans);
	}
	return 0;
}
