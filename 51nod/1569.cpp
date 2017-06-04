#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxs = 1001, maxl = 3323, mod = 1000000007, BLEN = 9, BASE = (int)1e9;
int p, m, len, num[maxs], n, seq[maxl], f[2][2][2][maxl], cur, pre = 1;
char str[maxs];
inline void mod_inc(int &x, int y)
{
	if((x += y) >= mod)
		x -= mod;
}
inline void mod_inc(int &x, int y, int z)
{
	x = (x + (LL)y * z) % mod;
}
inline int calc(int lim, int pdt, int cdt)
{
	int ret = (((lim + 1LL) * (lim + 2)) >> 1) % mod;
	if(cdt && (ret -= lim + 1) < 0)
		ret += mod;
	if(pdt && (ret = ((lim + 1LL) * p - ret) % mod) < 0)
		ret += mod;
	return ret;
}
int main()
{
	scanf("%d%d%s", &p, &m, str);
	len = strlen(str);
	for(int i = 0; i * BLEN < len; ++i)
	{
		int L = i * BLEN, R = std::min(L + BLEN, len) - 1;
		for(num[i] = 0; L <= R; --R)
			num[i] = (num[i] << 3) + (num[i] << 1) + (str[len - 1 - R] - '0');
	}
	len = (len - 1) / 9 + 1;
	while(!(len == 1 && !num[0]))
	{
		int &ret = seq[n++];
		for(int i = len - 1; i >= 0; --i)
		{
			LL tmp = (LL)ret * BASE + num[i];
			num[i] = tmp / p;
			ret = tmp % p;
		}
		for( ; len > 1 && !num[len - 1]; --len);
	}
	if(m > n)
	{
		puts("0");
		return 0;
	}
	f[cur][0][0][0] = 1; // gre = 0, dt = 0, cnt = 0
	for(int i = 0; i < n; ++i)
	{
		pre ^= 1;
		cur ^= 1;
		memset(f[cur], 0, sizeof f[cur]);
		int upp = seq[n - 1 - i];
		for(int gre = 0; gre < 2; ++gre)
			for(int pdt = 0; pdt < 2; ++pdt)
				for(int pcnt = 0; pcnt <= m; ++pcnt)
				{
					if(!f[pre][gre][pdt][pcnt])
						continue;
					for(int cdt = 0; cdt < 2; ++cdt)
					{
						int ccnt = std::min(pcnt + cdt, m);
						if(gre)
							mod_inc(f[cur][gre][cdt][ccnt], f[pre][gre][pdt][pcnt], calc(p - 1, pdt, cdt));
						else
						{
							if(upp)
								mod_inc(f[cur][1][cdt][ccnt], f[pre][gre][pdt][pcnt], calc(upp - 1, pdt, cdt));
							int tp = upp + 1 - cdt;
							if(pdt)
								tp = p - tp;
							mod_inc(f[cur][gre][cdt][ccnt], f[pre][gre][pdt][pcnt], tp);
						}
					}
				}
	}
	mod_inc(f[cur][0][0][m], f[cur][1][0][m]);
	printf("%d\n", f[cur][0][0][m]);
	return 0;
}s
