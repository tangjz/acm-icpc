#include <cstdio>
const int maxn = 1000001;
int n, tot, prime[maxn], f[maxn];
long long sum[maxn];
int main()
{
	for(int i = 2; i < maxn; ++i)
	{
		if(!f[i])
		{
			f[i] = i;
			prime[tot++] = i;
		}
		for(int j = 0; j < tot && (long long)i * prime[j] < maxn; ++j)
		{
			f[i * prime[j]] = f[i] == prime[j] ? prime[j] : 1;
			if(i % prime[j] == 0)
				break;
		}
		if(i > 2)
			sum[i] = sum[i - 1] + f[i];
	}
	while(scanf("%d", &n) != EOF)
		printf("%I64d\n", sum[n]);
	return 0;
}
