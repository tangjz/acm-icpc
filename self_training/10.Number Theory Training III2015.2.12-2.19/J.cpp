#include <cstdio>
const int maxa = 173206;
int tot, prime[maxa];
bool vis[maxa];
bool isprime(long long x)
{
	if(x < maxa)
		return !vis[x];
	for(int j = 0; j < tot; ++j)
		if(x % prime[j] == 0)
			return 0;
	return 1;
}
int main()
{
	for(int i = 2; i < maxa; ++i)
	{
		if(!vis[i])
			prime[tot++] = i;
		for(int j = 0; j < tot && (long long)i * prime[j] < maxa; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	int a, b;
	while(scanf("%d%d", &a, &b) == 2)
		puts(isprime((long long)a * a + 2ll * b * b) ? "Yes" : "No");
	return 0;
}
