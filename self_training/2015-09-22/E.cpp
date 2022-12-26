#include <cstdio>
#include <cstring>
const int maxn = 102, maxm = 11, inv2 = 6, mod = 1000000007;
typedef long long LL;
int n, f[2][maxn][maxm], cnt[maxm], sum, inv[maxn], fact[maxn], ans;
char str[maxn];
void inc(int &x, int y)
{
	x += y;
	if(x >= mod)
		x -= mod;
}
int main()
{
	inv[1] = 1;
	for(int i = 2; i < maxn; ++i)
		inv[i] = mod - (LL)mod / i * inv[mod % i] % mod;
	inv[0] = fact[0] = 1;
	for(int i = 1; i < maxn; ++i)
	{
		fact[i] = (LL)fact[i - 1] * i % mod;
		inv[i] = (LL)inv[i - 1] * inv[i] % mod;
	}
	while(scanf("%s", str) == 1)
	{
		sum = 0;
		memset(cnt, 0, sizeof cnt);
		n = strlen(str);
		int len = n + 1 >> 1, cur = 0, last = 1;
		memset(f[cur], 0, sizeof f[0]);
		f[cur][0][0] = 1;
		for(int i = 0; i < n; ++i)
		{
			++cnt[str[i] -= '0'];
			sum += str[i];
			cur ^= 1, last ^= 1;
			memset(f[cur], 0, sizeof f[0]);
			for(int j = 0; j <= i; ++j)
				for(int k = 0; k < maxm; ++k)
					if(f[last][j][k])
					{
						inc(f[cur][j][k], f[last][j][k]);
						inc(f[cur][j + 1][(k + str[i]) % maxm], f[last][j][k]);
					}
		}
		int res = sum * inv2 % maxm;
		ans = (LL)f[cur][len][res] * fact[n - len] % mod * fact[len] % mod;
		for(int i = 0; i < maxm; ++i)
			ans = (LL)ans * inv[cnt[i]] % mod;
		if(cnt[0])
		{
			sum = 0;
			memset(cnt, 0, sizeof cnt);
			cnt[0] = -1;
			int len = n >> 1, cur = 0, last = 1;
			memset(f[cur], 0, sizeof f[0]);
			f[cur][0][0] = 1;
			for(int i = 0; i < n; ++i)
			{
				++cnt[str[i]];
				sum += str[i];
				if(!cnt[str[i]])
					continue;
				cur ^= 1, last ^= 1;
				memset(f[cur], 0, sizeof f[0]);
				for(int j = 0; j <= i; ++j)
					for(int k = 0; k < maxm; ++k)
						if(f[last][j][k])
						{
							inc(f[cur][j][k], f[last][j][k]);
							inc(f[cur][j + 1][(k + str[i]) % maxm], f[last][j][k]);
						}
			}
			int res = sum * inv2 % maxm, tmp;
			tmp = (LL)f[cur][len][res] * fact[n - 1 - len] % mod * fact[len] % mod;
			for(int i = 0; i < maxm; ++i)
				tmp = (LL)tmp * inv[cnt[i]] % mod;
			ans -= tmp;
			if(ans < 0)
				ans += mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}
