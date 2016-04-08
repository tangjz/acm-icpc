#include <cstdio>
const int maxn = 10000001;
int tot, prime[maxn], fact[maxn], inv[maxn], f[maxn], t, n, m, p;
bool vis[maxn];
int main()
{
	scanf("%d%d", &t, &p);
	fact[1] = inv[1] = f[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		fact[i] = (long long)fact[i - 1] * i % p;
		inv[i] = (long long)inv[p % i] * (p - p / i) % p;
		f[i] = f[i - 1];
		if(!vis[i])
		{
			prime[tot++] = i;
			f[i] = (long long)f[i] * (i - 1) % p * inv[i] % p;
		}
		for(int j = 0; j < tot && (long long)i * prime[j] < maxn; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	while(t--)
	{
		scanf("%d%d", &n, &m);
		printf("%d\n", (long long)fact[n] * f[m] % p);
	}
	return 0;
}
