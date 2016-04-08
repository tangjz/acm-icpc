#include <cstdio>
const int maxn = 1001, maxk = 20001, mod = 1000000007;
int t, n, k, f[maxn][maxk];
inline int min(const int &x, const int &y)
{
	return x < y ? x : y;
}
int main()
{
	f[0][0] = 1;
	for(int i = 1; i < maxn; ++i)
		for(int j = 0, k = min(i * (i - 1) / 2, maxk - 1); j <= k; ++j)
		{
			f[i][j] = f[i - 1][j];
			if(j)
				f[i][j] += f[i][j - 1];
			if(j >= i)
				f[i][j] -= f[i - 1][j - i];
			if(f[i][j] < 0)
				f[i][j] += mod;
			else if(f[i][j] >= mod)
				f[i][j] -= mod;
		}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &k);
		printf("%d\n", f[n][k]);
	}
	return 0;
}
