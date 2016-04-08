#include <cstdio>
#include <cstring>
const int maxn = 200001;
int n, q, tot, prime[maxn], mu[maxn];
long long bit[maxn];
bool vis[maxn];
inline void scan(int &x)
{
	int ch;
	while((ch = getchar()) < '0' || ch > '9');
	x = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + (ch - '0');
}
void add(int x, int v)
{
	for( ; x <= n; x += x & -x)
		bit[x] += v;
}
long long sum(int x)
{
	long long ret = 0;
	for( ; x > 0; x -= x & -x)
		ret += bit[x];
	return ret;
}
int main()
{
	mu[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!vis[i])
		{
			prime[tot++] = i;
			mu[i] = -1;
		}
		for(int j = 0; j < maxn && (long long)i * prime[j] < maxn; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
			{
				mu[i * prime[j]] = 0;
				break;
			}
			else
				mu[i * prime[j]] = -mu[i];
		}
	}
	int Case = 0;
	while(scanf("%d%d", &n, &q) == 2 && n + q)
	{
		memset(bit, 0, sizeof bit);
		printf("Case #%d:\n", ++Case);
		while(q--)
		{
			int id, x, y, z;
			scan(id);
			if(id == 1)
			{
				scan(x), scan(y), scan(z);
				if(x % y != 0)
					continue;
				x /= y;
				for(int i = 1; (long long)i * i <= x; ++i)
				{
					if(x % i != 0)
						continue;
					if((long long)i * y <= n)
						add(i * y, mu[i] * z);
					if(i != x / i && (long long)x / i * y <= n)
						add(x / i * y, mu[x / i] * z);
				}
			}
			else
			{
				long long ans = 0;
				scan(x);
				for(int i = 1, j; i <= x; i = j + 1)
				{
					j = x / (x / i);
					ans += (x / i) * (sum(j) - sum(i - 1));
				}
				printf("%lld\n", ans);
			}
		}
	}
	return 0;
}
