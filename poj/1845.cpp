#include <cstdio>
const int mod = 9901;
int pow(int x, long long k)
{
	int ret = 1;
	while(k)
	{
		if(k & 1)
			ret = ret * x % mod;
		x = x * x % mod;
		k >>= 1;
	}
	return ret;
}
int sum(int x, long long k)
{
	if(!k)
		return 1;
	int ret = sum(x, k - 1 >> 1) * (1 + pow(x, (k >> 1) + 1)) % mod;
	if(!(k & 1))
	{
		ret += pow(x, k >> 1);
		if(ret >= mod)
			ret -= mod;
	}
	return ret;
}
int a, b, ans;
int main()
{
	scanf("%d%d", &a, &b);
	ans = 1;
	for(int i = 2; (long long)i * i <= a; ++i)
		if(a % i == 0)
		{
			int cnt = 0;
			while(a % i == 0)
			{
				a /= i;
				++cnt;
			}
			ans = ans * sum(i % mod, (long long)b * cnt) % mod;
		}
	if(a > 1)
		ans = ans * sum(a % mod, b) % mod;
	printf("%d\n", ans);
	return 0;
}
