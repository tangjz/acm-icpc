#include <cstdio>
const int maxn = 100000, maxk = 2000010;
int n, m, num[maxn + 100], k, tot, prime[maxk + 100];
char vis[maxk + 100];
int main()
{
	vis[1] = 1;
	for(int i = 2; i < maxk; ++i)
	{
		if(!vis[i])
			prime[tot++] = i;
		for(int j = 0; j < tot; ++j)
		{
			if(i * (long long)prime[j] >= maxk)
				break;
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	while(scanf("%d%d", &n, &m) == 2)
	{
		for(int i = 1; i <= n; ++i)
		{
			num[i] = 0;
			for(int j = 1, x; j <= m; ++j)
			{
				scanf("%d", &x);
				num[i] |= vis[x] << j;
			}
		}
		scanf("%d", &k);
		while(k--)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			puts(x < 1 || x > n || y < 1 || y > m || (num[x] & (1 << y)) ? "NononO" : "YeSYESYeS");
		}
	}
	return 0;
}
