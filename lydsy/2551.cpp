#include <cstdio>
const int maxn = 21, maxs = 13, maxm = 241;
int n, m, a[maxn], R[maxn][maxs], D[maxn][maxs];
int tot, prime[maxm], f[maxm], cnt[maxm];
int len, num[maxm];
bool can[maxn][maxs];
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		int cnt;
		scanf("%d", a + i);
		m += a[i];
		for(int j = 0; j < a[i]; ++j)
			can[i][j] = 1;
	}
	for(int i = 2; i <= m; ++i)
	{
		if(!f[i])
			prime[tot++] = f[i] = i;
		for(int j = 0; j < tot && i * prime[j] <= m; ++j)
		{
			f[i * prime[j]] = prime[j];
			if(i % prime[j] == 0)
				break;
		}
		++cnt[i];
	}
	for(int i = n - 1; i >= 0; --i)
		for(int j = a[i] - 1; j >= 0; --j)
		{
			R[i][j] = can[i][j + 1] ? R[i][j + 1] + 1 : 1;
			D[i][j] = can[i + 1][j] ? D[i + 1][j] + 1 : 1;
			--cnt[R[i][j] + D[i][j] - 1];
		}
	for(int i = m; i >= 2; --i)
		if(i != f[i])
		{
			cnt[f[i]] += cnt[i];
			cnt[i / f[i]] += cnt[i];
		}
	len = num[0] = 1;
	for(int i = 0; i < tot; ++i)
		for(int j = 0; j < cnt[prime[i]]; ++j)
		{
			for(int k = 0; k < len; ++k)
				num[k] *= prime[i];
			for(int k = 0; k < len; ++k)
				if(num[k] >= 10)
				{
					num[k + 1] += num[k] / 10;
					num[k] %= 10;
				}
			for( ; num[len]; ++len)
				if(num[len] >= 10)
				{
					num[len + 1] += num[len] / 10;
					num[len] %= 10;
				}
		}
	for(int i = len - 1; i >= 0; --i)
		printf("%d", num[i]);
	putchar('\n');
	return 0;
}

