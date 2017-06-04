#include <stdio.h>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxn = 19, maxd = 10, maxm = 49, mod = 2520;
const LL maxv = (LL)1e18;
int tot, seq[maxm], pos[mod + 1];
LL f[maxn][maxm][mod + 1];
LL solve(LL lim)
{
	LL ret = 0;
	static char dig[maxn];
	int len = sprintf(dig, "%lld", lim), v = 1, r = 0;
	std::reverse(dig, dig + len);
	for(int i = len - 1; i >= 0; --i)
	{
		int x = dig[i] - '0';
		for(int y = 0; y < x; ++y)
		{
			int vv = y ? v / std::__gcd(v, y) * y : v;
			int rr = (r * 10 + y) % mod;
			ret += f[i][pos[vv]][rr];
		}
		v = x ? v / std::__gcd(v, x) * x : v;
		r = (r * 10 + x) % mod;
	}
	return ret;
}
int main()
{
	memset(pos, -1, sizeof pos);
	for(int i = 0; i < (1 << (maxd - 1)); ++i)
	{
		int val = 1;
		for(int j = 1; j < maxd; ++j)
			if((i >> (j - 1)) & 1)
				val *= j / std::__gcd(val, j);
		if(pos[val] == -1)
		{
			pos[val] = tot;
			seq[tot++] = val;
		}
	}
	for(int i = 0; i < tot; ++i)
		for(int j = 0; j < mod; j += seq[i])
			f[0][i][j] = 1;
	for(int i = 1; i < maxn; ++i)
		for(int j = 0; j < tot; ++j)
		{
			int u = seq[j];
			for(int k = 0; k < mod; ++k)
				for(int o = 0; o < maxd; ++o)
				{
					int v = o ? u / std::__gcd(u, o) * o : u;
					f[i][j][k] += f[i - 1][pos[v]][(k * 10 + o) % mod];
				}
		}
	int t;
	LL L, R;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld%lld", &L, &R);
		printf("%lld\n", solve(R + 1) - solve(L));
	}
	return 0;
}
