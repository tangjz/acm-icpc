#include <cstdio>
typedef long long LL;
const int maxn = 20, maxd = 10, mod = 1000000007;
int sum[maxd], sum2[maxd], len, dig[maxn];
int calc(LL x)
{
	int ret = 0;
	for(len = 0; x > 0; dig[len++] = x % 10, x /= 10);
	LL tmp = 9;
	for(int i = 1; i < len; ++i)
	{
		ret = (ret + (tmp / 90) % mod * 2 * sum[maxd - 1] * sum[maxd - 1]) % mod;
		if(i > 2)
			ret = (ret + (tmp / 100) % mod * ((i - 2 >> 1) << 1) * sum[maxd - 1] * sum[maxd - 1]) % mod;
		if(i == 1)
			ret = (ret + (tmp / 9) % mod * sum2[maxd - 1]) % mod;
		else if(i & 1)
			ret = (ret + (tmp / 10) % mod * sum2[maxd - 1]) % mod;
		tmp *= 10;
	}
	for(int i = len - 1; i >= 0; --i)
	{
		int iL = i == len - 1 ? 1 : 0, iR = dig[i] - 1;
		if(iL > iR)
			continue;
		int iS = 0, iS2 = 0;
		for(int j = iL; j <= iR; ++j)
		{
			iS += j;
			iS2 += j * j;
		}
		LL total = iR - iL + 1;
		for(int j = 0; j < i; ++j)
			total *= 10;
		for(int j = 0, k = len - 1; j < len; ++j, --k)
		{
			int jS = 0, kS = 0;
			LL cnt = total;
			if(j < i)
			{
				jS = sum[maxd - 1];
				cnt /= maxd;
			}
			else if(j == i)
			{
				jS = iS;
				cnt /= iR - iL + 1;
			}
			else
				jS = dig[j];
			if(j == k)
			{
				if(j < i)
					jS = sum2[maxd - 1];
				else if(j == i)
					jS = iS2;
				else
					jS = dig[j] * dig[j];
				kS = 1;
			}
			else if(k < i)
			{
				kS = sum[maxd - 1];
				cnt /= maxd;
			}
			else if(k == i)
			{
				kS = iS;
				cnt /= iR - iL + 1;
			}
			else
				kS = dig[k];
			ret = (ret + cnt % mod * jS * kS) % mod;
		}
	}
	return ret;
}
int main()
{
	for(int i = 1; i < maxd; ++i)
	{
		sum[i] = sum[i - 1] + i;
		sum2[i] = sum2[i - 1] + i * i;
	}
	LL l, r;
	scanf("%lld%lld", &l, &r);
	int ans = calc(r + 1) - calc(l);
	if(ans < 0)
		ans += mod;
	printf("%d\n", ans);
	return 0;
}
