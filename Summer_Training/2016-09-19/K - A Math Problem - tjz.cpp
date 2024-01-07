#include <stdio.h>
#include <cstring>
typedef long long LL;
const int maxp = 5, prime[maxp] = {3, 5, 17, 257, 65537};
const int maxl = 60, maxv = 65537;
int pw[maxp][maxl], t, id, len;
LL cnt[maxp][maxl][maxv], n, f[maxv];
int main()
{
	for(int o = 0; o < maxp; ++o)
	{
		const int &mod = prime[o];
		pw[o][0] = cnt[o][0][0] = 1;
		for(int i = 1; i < maxl; ++i)
		{
			pw[o][i] = 3 * pw[o][i - 1] % mod;
			for(int j = 0; j < mod; ++j)
			{
				cnt[o][i][3 * j % mod] += cnt[o][i - 1][j];
				cnt[o][i][(3 * j + 1) % mod] += cnt[o][i - 1][j];
			}
		}
	}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld%d", &n, &id);
		++n;
		for(int o = 0; o < maxp; ++o)
			if(id == prime[o])
			{
				id = o;
				break;
			}
		const int &mod = prime[id];
		memset(f, 0, mod * sizeof(LL));
		for(len = 1; 1LL << len <= n; ++len);
		for(int i = len - 1, val = 0; i >= 0; --i)
		{
			if((n >> i) & 1)
			{
				int delta = 3LL * val * pw[id][i] % mod;
				for(int j = 0, k = delta; j < mod; ++j, k = k + 1 < mod ? k + 1 : 0)
					f[k] += cnt[id][i][j];
			}
			val = (3 * val + ((n >> i) & 1)) % mod;
		}
		--f[0];
		LL ans = 0;
		for(int i = 0; i < mod; ++i)
			ans ^= f[i];
		printf("%lld\n", ans);
	}
	return 0;
}
