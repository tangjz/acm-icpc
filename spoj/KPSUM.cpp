#include <cstdio>
long long n, len, num[17], s[10], ans, f[16];
int main()
{
	int i;
	for(f[i = 0] = 1, ++i; i <= 15; ++i) f[i] = f[i - 1] * 10;
	for(i = 1; i < 10; ++i) s[i] = s[i - 1] + i;
	while(scanf("%lld", &n) != EOF && n)
	{
		if(n < 10)
		{
			printf("%lld\n", n & 1 ? n + 1 >> 1 : -(n + 1 >> 1));
			continue;
		}
		ans = 5;
		len = 0;
		for(long long tmp = n; tmp; tmp /= 10) num[++len] = tmp % 10;
		for(i = 2; i < len; ++i)
			if(i & 1) ans += 9 * f[i - 1] >> 1;
			else ans -= 45 * f[i - 2];
		if(len & 1)
		{
			if(n & 1) ans += n + 1 - f[len - 1] >> 1;
			else
			{
				ans += n - f[len - 1] >> 1;
				for(i = len; i; --i)
					if(i & 1) ans -= num[i];
					else ans += num[i];
			}
		}
		else
			for(i = len; i; --i)
				if(num[i])
				{
					if(i & 1) ans += s[num[i] - 1] * f[i - 1] + num[i] * (n % f[i - 1] + 1);
					else ans += (45 * (num[i] - (i == len)) - s[num[i] - 1] * 10) * f[i - 2] - num[i] * (n % f[i - 1] + 1);
				}
		printf("%lld\n", ans);
	}
	return 0;
}
