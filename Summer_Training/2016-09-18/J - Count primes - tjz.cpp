#include <cmath>
#include <stdio.h>
typedef long long LL;
const int maxp = 1000001;
int tot, prime[maxp], s[maxp];
LL solve(LL n, int k)
{
	if(k <= 1)
		return n - (k ? (n >> 1) : 0);
	if(n <= prime[k - 1])
		return 1;
	if(n < maxp)
	{
		if(s[(int)n] <= k)
			return 1;
		if(s[(int)sqrt(n)] <= k)
			return s[n] - k + 1;
	}
	return solve(n, k - 1) - solve(n / prime[k - 1], k - 1);
}
int main()
{
	for(int i = 2; i < maxp; ++i)
	{
		if(!s[i])
			prime[tot++] = i;
		for(int j = 0, k = (maxp - 1) / i; j < tot && prime[j] <= k; ++j)
		{
			s[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
		s[i] = s[i - 1] + (!s[i]);
	}
	LL n, ans;
	while(scanf("%I64d", &n) == 1)
	{
		int sqn = (int)sqrt(n);
		ans = solve(n, s[sqn]) + s[sqn] - 1;
		printf("%I64d\n", ans);
	}
	return 0;
}
