#include <stdio.h>
const int maxn = 5000000;
int tot, prime[maxn + 1], f[maxn + 1], t, a, b;
int main()
{
	for(int i = 2; i <= maxn; ++i)
	{
		if(!f[i])
		{
			prime[tot++] = i;
			f[i] = 1;
		}
		for(int j = 0, k = maxn / i; j < tot && prime[j] <= k; ++j)
		{
			f[i * prime[j]] = f[i] + 1;
			if(i % prime[j] == 0)
				break;
		}
		f[i] += f[i - 1];
	}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &a, &b);
		printf("%d\n", f[a] - f[b]);
	}
	return 0;
}
