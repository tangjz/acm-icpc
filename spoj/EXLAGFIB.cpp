
#include <stdio.h>
typedef long long LL;
const int maxp = 3, pr[maxp] = {421, 563, 4219}, sei[maxp] = {933491721, 257548855, 808959499};
const int maxn = 4219, mod = 1000000037;
int c[3][maxn][maxn];
int C(int n, int m)
{
	int ret = 0;
	for(int i = 0; i < maxp; ++i)
	{
		int tmp = 1;
		for(int tn = n, tm = m; tn; tn /= pr[i], tm /= pr[i])
		{
			int pn = tn % pr[i], pm = tm % pr[i];
			if(pn < pm)
			{
				tmp = 0;
				break;
			}
			tmp = (LL)tmp * c[i][pn][pm] % mod;
		}
		ret = (ret + (LL)sei[i] * tmp) % mod;
	}
	return ret;
}
int mod_pow(int x, int k)
{
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
int main()
{
	for(int id = 0; id < maxp; ++id)
		for(int i = 0; i < pr[id]; ++i)
		{
			c[id][i][0] = c[id][i][i] = 1;
			for(int j = 1; j < i; ++j)
				if((c[id][i][j] = c[id][i - 1][j - 1] + c[id][i - 1][j]) >= pr[id])
					c[id][i][j] -= pr[id];
		}
	int t, n, a, b, p, q, ans;
	scanf("%d", &t);
	while(t--)
	{
		ans = 0;
		scanf("%d%d%d%d%d", &n, &a, &b, &p, &q);
		n -= b - 1;
		for(int i = 0, ib = 0; ib <= n; ++i, ib += b)
		{
			if((n - ib) % a)
				continue;
			int j = (n - ib) / a;
			ans = (ans + (LL)mod_pow(q, i) * mod_pow(p, j) % mod * C(i + j, i)) % mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}
