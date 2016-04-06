#include <cstdio>
const int maxn = 50001;
int n, m, tot, prime[maxn], fact[maxn], cnt[maxn], ans;
bool vis[maxn];
int main()
{
	scanf("%d%d", &n, &m);
	++cnt[n];
	--cnt[m];
	--cnt[n - m];
	for(int i = 2; i <= n; ++i)
		if(!vis[i])
		{
			prime[tot++] = i;
			for(int j = i; j <= n; j += i)
			{
				vis[j] = 1;
				fact[j] = i;
			}
		}
	for(int i = n; i >= 2; --i)
		cnt[i] += cnt[i + 1];
	for(int i = n; i >= 2; --i)
		if(fact[i] != i)
		{
			cnt[fact[i]] += cnt[i];
			cnt[i / fact[i]] += cnt[i];
		}
	for(int i = 0; i < tot; ++i)
		if(cnt[prime[i]])
			++ans;
	printf("%d\n", ans);
	return 0;
}
