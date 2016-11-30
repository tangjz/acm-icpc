#include <cstdio>
const int maxn = 1e6 + 1, maxa = 1e7 + 1;
int n, lim, tot, prime[maxa], fact[maxa];
long long cnt[maxa], L, R, M;
bool vis[maxa];
bool check()
{
	for(int i = 0; i < tot; ++i)
	{
		long long tmp = M, sum = 0;
		while(tmp)
		{
			tmp /= prime[i];
			sum += tmp;
		}
		if(sum < cnt[prime[i]])
			return 0;
	}
	return 1;
}
int main()
{
	scanf("%d", &n);
	for(int i = 0, a; i < n; ++i)
	{
		scanf("%d", &a);
		R += a;
		++cnt[a];
		if(lim < a)
			lim = a;
	}
	for(int i = 2; i <= lim; ++i)
		if(!vis[i])
		{
			prime[tot++] = i;
			for(int j = i; j <= lim; j += i)
			{
				vis[j] = 1;
				fact[j] = i;
			}
		}
	for(int i = lim; i >= 2; --i)
		cnt[i] += cnt[i + 1];
	for(int i = lim; i >= 2; --i)
		if(fact[i] != i)
		{
			cnt[fact[i]] += cnt[i];
			cnt[i / fact[i]] += cnt[i];
		}
	L = 1;
	while(L < R)
	{
		M = L + R >> 1;
		if(check())
			R = M;
		else
			L = M + 1;
	}
	printf("%I64d\n", L);
	return 0;
}
