#include <cstdio>
const int maxn = 10000001;
int k, p, inv[maxn], tmp1, tmp2, tmp3, cnt, ans;
int pow(int x, int k)
{
	int ret = 1;
	while(k)
	{
		if(k & 1)
			ret = (long long)ret * x % p;
		x = (long long)x * x % p;
		k >>= 1;
	}
	return ret;
}
int main()
{
	scanf("%d%d", &k, &p);
	inv[1] = 1;
	for(int i = 2, j = k + 1 < p ? k + 1 : p; i < j; ++i)
		inv[i] = ((long long)p - p / i) * inv[p % i] % p;
	ans = 1;
	for(int i = 1, tmp1 = 1, tmp3 = 1; i <= k; ++i)
	{
		tmp1 = (tmp1 << 1) % p;
		tmp2 = k - i + 1;
		while(tmp2 % p == 0)
		{
			++cnt;
			tmp2 /= p;
		}
		tmp3 = (long long)tmp2 * tmp3 % p;
		tmp2 = i;
		while(tmp2 % p == 0)
		{
			--cnt;
			tmp2 /= p;
		}
		tmp3 = (long long)tmp3 * inv[tmp2 % p] % p;
		ans ^= cnt ? 0 : (long long)tmp1 * tmp3 % p;
	}
	printf("%d\n", ans);
	return 0;
}
