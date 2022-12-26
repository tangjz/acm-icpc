#include <stdio.h>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxn = 19, maxd = 10, maxc = 163, maxs = 1459;
const LL maxv = (LL)1e18;
int tot, pr[maxs], d[maxs];
LL f[maxn][maxc][maxs];
LL solve(LL lim)
{
	LL ret = 0;
	static char dig[maxn];
	int len = sprintf(dig, "%lld", lim), c = 0, s = 0;
	std::reverse(dig, dig + len);
	for(int i = len - 1; i >= 0; --i)
	{
		int x = dig[i] - '0';
		for(int y = 0; y < x; ++y)
			ret += f[i][c + y][s + y * y];
		c += x;
		s += x * x;
	}
	return ret;
}
int main()
{
	d[0] = d[1] = -1;
	for(int i = 2; i < maxs; ++i)
	{
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxs; ++j)
		{
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	for(int i = 0; i < maxc; ++i)
		for(int j = i; j < maxs; ++j)
			f[0][i][j] = d[i] == i && d[j] == j;
	for(int i = 1; i < maxn; ++i)
		for(int j = 0; j < maxc; ++j)
			for(int k = j; k < maxs; ++k)
				for(int o = 0; o < maxd && j + o < maxc && k + o * o < maxs; ++o)
					f[i][j][k] += f[i - 1][j + o][k + o * o];
	int t;
	LL L, R;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld%lld", &L, &R);
		printf("%lld\n", solve(std::min(R + 1, maxv)) - solve(L));
	}
	return 0;
}
