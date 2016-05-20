#include <cstdio>
#include <algorithm>
const int maxd = 6, mod = 2333;
typedef long long LL;
int pw2[mod], f[mod][mod], t, nlen, ndig[maxd], mlen, mdig[maxd], s[maxd], ans;
LL n, m;
int main()
{
	pw2[0] = f[0][0] = 1;
	for(int i = 1; i < mod; ++i)
	{
		if((pw2[i] = pw2[i - 1] << 1) >= mod)
			pw2[i] -= mod;
		f[i][0] = f[i][i] = 1;
		for(int j = 1; j < i; ++j)
			if((f[i][j] = f[i - 1][j - 1] + f[i - 1][j]) >= mod)
				f[i][j] -= mod;
	}
	for(int i = 1; i < mod; ++i)
		for(int j = 1; j <= i; ++j)
			if((f[i][j] += f[i][j - 1]) >= mod)
				f[i][j] -= mod;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld%lld", &n, &m);
		++m;
		for(nlen = 0; n > 0; ndig[nlen++] = n % mod, n /= mod);
		for(mlen = 0; m > 0; mdig[mlen++] = m % mod, m /= mod);
		for(int i = 0; i < nlen; ++i)
			if((s[i] = (i > 0 ? s[i - 1] : 0) + ndig[i]) >= mod - 1)
				s[i] -= mod - 1;
		ans = 0;
		for(int i = mlen - 1, val = 1; i >= 0; --i)
		{
			if(mdig[i] > 0)
				ans = (ans + val * f[ndig[i]][std::min(ndig[i], mdig[i] - 1)] * (LL)(i > 0 ? pw2[s[i - 1]] : 1)) % mod;
			if(mdig[i] > ndig[i])
				break;
			if((val = val * (f[ndig[i]][mdig[i]] - (mdig[i] > 0 ? f[ndig[i]][mdig[i] - 1] : 0)) % mod) < 0)
				val += mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}
