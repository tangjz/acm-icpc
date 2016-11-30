#include <cstdio>
typedef long long LL;
const int maxn = 100001, mod = 1000000009;
int t, n, p[maxn], inv[maxn], ans;
bool vis[maxn];
int mod_pow(int x, int k)
{
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
int main()
{
	inv[1] = 1;
	for(int i = 2; i < maxn; ++i)
		inv[i] = mod - mod / i * (LL)inv[mod % i] % mod;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d", p + i);
			vis[i] = 0;
		}
		ans = 1;
		for(int i = 1, j, cnt = 0, tmp; i <= n; ++i)
		{
			if(vis[i])
				continue;
			for(j = i, tmp = 0; !vis[j]; j = p[j], ++tmp)
				vis[j] = 1;
			if(tmp > 1)
			{
				ans = (LL)ans * mod_pow(tmp, tmp - 2) % mod;
				for(j = 1; j < tmp; ++j)
					ans = (LL)ans * inv[j] % mod * (++cnt) % mod;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
