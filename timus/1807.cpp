#include <cmath>
#include <stdio.h>
#include <cassert>
#include <algorithm>
typedef double DB;
const int maxn = 32001, maxm = 151, maxo = 501;
int tot, pr[maxn], d[maxn], n, lim, g[maxm][maxn], sz, out[maxo];
DB f[maxm][maxn];
int main()
{
	scanf("%d", &n);
	for(lim = 1; lim * lim <= n; ++lim);
	for(int i = 2; i < lim; ++i)
	{
		if(!d[i])
		{
			pr[++tot] = d[i] = i;
			if(n % i == 0)
			{
				lim = i;
				break;
			}
		}
		for(int j = 0, k; (k = i * pr[j]) < lim; ++j)
		{
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	assert(lim * lim <= n);
	int r = n / lim;
	if(lim <= 3)
	{
		printf("%d %d\n", r, n - r);
		return 0;
	}
	if(tot >= maxm)
		tot = maxm - 1;
	for(int i = 1; i <= tot; ++i)
		for(int j = 0; j <= lim; ++j)
		{
			f[i][j] = f[i - 1][j];
			g[i][j] = 0;
			DB val = log((DB)pr[i]), dt = val;
			for(int k = pr[i]; k <= j; k *= pr[i], val += dt)
				if(f[i][j] < f[i - 1][j - k] + val)
				{
					f[i][j] = f[i - 1][j - k] + val;
					g[i][j] = k;
				}
		}
	for(int i = tot; i > 0; lim -= g[i--][lim])
		if(g[i][lim])
			out[sz++] = r * g[i][lim];
	while(lim--)
		out[sz++] = r;
	std::sort(out, out + sz);
	for(int i = 0; i < sz; ++i)
		printf("%d%c", out[i], " \n"[i == sz - 1]);
	return 0;
}
