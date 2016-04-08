#include <cstdio>
typedef long long LL;
const int maxn = 200001, mod = 999999599;
int n, m, f[maxn];
int mod_pow(int x, int k)
{
	int ret = 1;
	while(k)
	{
		if(k & 1)
			ret = (LL)ret * x % mod;
		x = (LL)x * x % mod;
		k >>= 1;
	}
	return ret;
}
int main()
{
	scanf("%d%d", &n, &m);
	f[0] = 1;
	for(int i = 1; i <= n; ++i)
	{
		LL tmp = 0;
		for(int j = 1; j * (3 * j - 1) >> 1 <= i; ++j)
			if(j & 1)
				tmp += f[i - (j * (3 * j - 1) >> 1)];
			else
				tmp -= f[i - (j * (3 * j - 1) >> 1)];
		for(int j = 1; j * (3 * j + 1) >> 1 <= i; ++j)
			if(j & 1)
				tmp += f[i - (j * (3 * j + 1) >> 1)];
			else
				tmp -= f[i - (j * (3 * j + 1) >> 1)];
		f[i] = tmp % (mod - 1);
		if(f[i] < 0)
			f[i] += mod - 1;
	}
	printf("%d\n", mod_pow(m, f[n]));
	return 0;
}
