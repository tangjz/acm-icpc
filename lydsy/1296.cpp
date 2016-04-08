#include <cstdio>
const int maxn = 52, maxt = 2501;
int n, m, t, s[maxn], f[maxn][maxn], g[maxt];
char str[maxn];
int min(int x, int y)
{
	return x < y ? x : y;
}
int max(int x, int y)
{
	return x < y ? y : x;
}
void upd(int &x, int y)
{
	if(x < y)
		x = y;
}
int main()
{
	scanf("%d%d%d", &n, &m, &t);
	for(int i = 0; i < n; ++i)
	{
		scanf("%s", str + 1);
		for(int j = 1; j <= m; ++j)
			s[j] = s[j - 1] + (str[j] == '1');
		for(int j = 1; j <= m; ++j)
			for(int R = 1; R <= m; ++R)
			{
				f[R][j] = 0;
				for(int L = 0; L < R; ++L)
					upd(f[R][j], f[L][j - 1] + max(s[R] - s[L], R - L - s[R] + s[L]));
			}
		for(int j = t; j; --j)
			for(int k = min(j, m); k; --k)
				upd(g[j], g[j - k] + f[m][k]);
	}
	for(int i = 1; i <= t; ++i)
		upd(g[0], g[i]);
	printf("%d\n", g[0]);
	return 0;
}
