#include <cstdio>
const int maxn = 50001;
int n, m, a[maxn], s[maxn], f[maxn], g[maxn];
bool check(int lim)
{
	int i, pL, pR;
	f[0] = g[0] = 1;
	// first row
	for(i = 1; i <= n && s[i] + (i - 1) <= m; ++i)
	{
		f[i] = s[i] + (i - 1) * lim >= m;
		g[i] = g[i - 1] + f[i];
	}
	// middle row
	for(pL = 1, pR = 1; i <= n; ++i)
	{
		for( ; pL < i && s[i] - s[pL] + (i - pL - 1) > m; ++pL);
		for( ; pR < i && s[i] - s[pR] + (i - pR - 1) * lim >= m; ++pR);
		// valid : [pL : pR)
		f[i] = pL < pR && g[pR - 1] - g[pL - 1] > 0;
		g[i] = g[i - 1] + f[i];
	}
	// last row
	if(f[n])
		return 1;
	for(i = n; i > 0 && s[n] - s[i - 1] + (n - i) <= m; --i)
		if(f[i - 1])
			return 1;
	return 0;
}
int main()
{
	while(scanf("%d%d", &m, &n) == 2 && n + m)
	{
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d", a + i);
			s[i] = s[i - 1] + a[i];
		}
		int L = 1, R = m - 2;
		while(L < R)
		{
			int M = (L + R) >> 1;
			if(check(M))
				R = M;
			else
				L = M + 1;
		}
		printf("%d\n", L);
	}
	return 0;
}
