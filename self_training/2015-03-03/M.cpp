#include <cstdio>
const int maxn = 100001;
int t, n, m, k, tot, prime[maxn], mu[maxn], smu[maxn];
long long ans1, ans2;
bool vis[maxn];
void swap(int &x, int &y)
{
	int t = x;
	x = y;
	y = t;
}
int main()
{
	mu[1] = smu[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!vis[i])
		{
			prime[tot++] = i;
			mu[i] = -1;
		}
		for(int j = 0; j < tot && i * prime[j] < maxn; ++j)
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
		smu[i] = smu[i - 1] + mu[i];
	}
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%*d%d%*d%d%d", &n, &m, &k);
		if(!k)
		{
			printf("Case %d: 0\n", Case);
			continue;
		}
		n /= k;
		m /= k;
		if(n > m)
			swap(n, m);
		ans1 = ans2 = 0;
		for(int i = 1, j; i <= n; i = j + 1)
		{
			j = n / (n / i) < m / (m / i) ? n / (n / i) : m / (m / i);
			ans1 += (long long)(n / i) * (m / i) * (smu[j] - smu[i - 1]);
		}
		for(int i = 1, j; i <= n; i = j + 1)
		{
			j = n / (n / i);
			ans2 += (long long)(n / i) * (n / i) * (smu[j] - smu[i - 1]);
		}
		printf("Case %d: %I64d\n", Case, ans1 - (ans2 >> 1));
	}
	return 0;
}
