#include <cstdio>
const int maxn = 1e6 + 1, mod = 1e9 + 7;
int n, m, k, cnt[maxn], pow2[maxn], ans;
int main()
{
	scanf("%d%d%d", &n, &m, &k);
	++k;
	while(m--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		if(u + 1 != v && u + k != v)
		{
			puts("0");
			return 0;
		}
		if(u + k == v)
			cnt[u] = 1;
	}
	for(int i = 1; i <= n; ++i)
		cnt[i] += cnt[i - 1];
	for(int i = k + 1; i <= n; ++i)
		if(cnt[i] - cnt[i - 1] && cnt[i - k])
		{
			puts("0");
			return 0;
		}
	pow2[0] = 1;
	for(int i = 1; i <= n; ++i)
	{
		pow2[i] = pow2[i - 1] << 1;
		if(pow2[i] >= mod)
			pow2[i] -= mod;
	}
	ans = !cnt[n];
	for(int i = 1; i <= n - k; ++i)
		if(cnt[i] == cnt[n])
		{
			if(i <= k)
				ans += pow2[i - cnt[i - 1] - 1];
			else if(!cnt[i - k])
				ans += pow2[k - cnt[i - 1] - 1];
			if(ans >= mod)
				ans -= mod;
		}
	printf("%d\n", ans);
	return 0;
}
