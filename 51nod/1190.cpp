#include <stdio.h>
typedef long long LL;
const int maxn = 31623, maxs = 10, mod = 1000000007;
int tot, prime[maxn], t, a, b, cnt, s[maxs], c[maxs], ans;
bool vis[maxn];
inline LL num1(int x)
{
	return (x * (x + 1LL) >> 1) % mod;
}
void dfs(int dep, int x, int phi, int fff)
{
	if(dep == cnt)
	{
		ans = (ans + ((LL)x * phi >> 1) - num1(a / x) * fff) % mod;
		return;
	}
	dfs(dep + 1, x, phi, fff);
	for(int i = 1, now = s[dep]; i <= c[dep]; ++i, now *= s[dep])
		dfs(dep + 1, x * now, phi * (now - now / s[dep]), fff * (1 - s[dep]));
}
int main()
{
	for(int i = 2; i < maxn; ++i)
	{
		if(!vis[i])
			prime[tot++] = i;
		for(int j = 0, o; j < tot && (o = i * prime[j]) < maxn; ++j)
		{
			vis[o] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &a, &b);
		--a;
		int tmp = b;
		cnt = 0;
		for(int i = 0; i < tot && prime[i] * prime[i] <= tmp; ++i)
			if(tmp % prime[i] == 0)
			{
				for(c[cnt] = 0; tmp % prime[i] == 0; tmp /= prime[i], ++c[cnt]) ;
				s[cnt++] = prime[i];
			}
		if(tmp > 1)
		{
			c[cnt] = 1;
			s[cnt++] = tmp;
		}
		ans = 1;
		dfs(0, 1, 1, 1);
		ans = (LL)ans * b % mod;
		if(ans < 0)
			ans += mod;
		printf("%d\n", ans);
	}
	return 0;
}
