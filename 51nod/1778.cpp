#include <stdio.h>
#include <cstring>
//#include <cassert>
typedef long long LL;
const int maxn = 1000001;
int tot, prime[maxn / 12 + 1], pw[maxn], inv[maxn];
int len, num[maxn], k, m, ans;
char str[maxn];
int rem(int len, int num[], int mod)
{
	int ret = 0;
	for(int i = len - 1; i >= 0; --i)
		ret = (ret * 10 + num[i]) % mod;
	return ret;
}
int div(int &len, int num[], int mod)
{
	for(int i = len - 1; i > 0; --i)
	{
		num[i - 1] += num[i] % mod * 10;
		num[i] /= mod;
	}
	int ret = num[0] % mod;
	num[0] /= mod;
	for( ; len > 1 && !num[len - 1]; --len);
	return ret;
}
int mod_pow(int x, int k)
{
	int ret = 1;
	while(k)
	{
		if(k & 1)
			ret = (LL)ret * x % m;
		x = (LL)x * x % m;
		k >>= 1;
	}
	return ret;
}
int main()
{
	scanf("%s%d%d", str, &k, &m); //assert(scanf("%s%d%d", str, &k, &m) == 3 && 1 <= k && k <= maxn && 2 <= m && m <= maxn);
	/*{
		for(int i = 2; i <= m / i; ++i)
			assert(m % i != 0);
	}*/
	len = strlen(str);
	/*assert(len <= maxn);
	if(len <= 7)
	{
		int n;
		sscanf(str, "%d", &n);
		assert(k <= n);
	}*/
	for(int i = 0; i < len; ++i)
		num[i] = str[len - 1 - i] - '0';
	inv[1] = 1;
	for(int i = 2; i < m; ++i)
		inv[i] = m - m / i * (LL)inv[m % i] % m;
	pw[1] = 1;
	for(int i = 2; i < m; ++i)
	{
		if(!pw[i])
		{
			prime[tot++] = i;
			pw[i] = mod_pow(i, k);
		}
		for(int j = 0, lim = (m - 1) / i; j < tot && prime[j] <= lim; ++j)
		{
			pw[i * prime[j]] = (LL)pw[i] * pw[prime[j]] % m;
			if(i % prime[j] == 0)
				break;
		}
	}
	int nR = div(len, num, m), coeff = 1;
	ans = (LL)pw[nR] * pw[nR] % m;
	for(int i = 1, j = nR - 1; i <= nR; ++i, --j)
	{
		coeff = (LL)coeff * (nR + 1 - i) % m * inv[i] % m;
		ans = (ans + (LL)(pw[i] - pw[j]) * (pw[i] - pw[j]) % m * coeff) % m;
	}
	ans = (LL)ans * mod_pow(2, rem(len, num, m - 1)) % m;
	printf("%d\n", ans);
	return 0;
}
