#include <stdio.h>
#include <cstring>
typedef long long LL;
const int maxd = 10, mod = 1000000007;
int t, n, f[maxd][1 << maxd], g[maxd][1 << maxd], cnt[1 << maxd], tot, msk[maxd], ans;
bool vis[maxd];
void dfs(int dep)
{
	if(dep == maxd)
	{
		int ways = 1;
		for(int i = 0; i < tot; ++i)
			ways = (LL)ways * cnt[msk[i]] % mod;
		if((ans += ways) >= mod)
			ans -= mod;
		return;
	}
	dfs(dep + 1);
	for(int i = 0; i < tot; ++i)
	{
		msk[i] |= 1 << dep;
		dfs(dep + 1);
		msk[i] ^= 1 << dep;
	}
	msk[tot++] = 1 << dep;
	dfs(dep + 1);
	msk[--tot] = 0;
}
int main()
{
	char str[maxd + 1];
	f[0][0] = g[0][0] = 1;
	for(int i = 1; i < maxd; ++i)
	{
		for(int j = 1; j < maxd; ++j)
			for(int k = 0; k < 1 << maxd; ++k)
				f[i][k | (1 << j)] += g[i - 1][k];
		for(int j = 0; j < maxd; ++j)
			for(int k = 0; k < 1 << maxd; ++k)
				g[i][k | (1 << j)] += g[i - 1][k];
	}
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d", &n);
		int len = sprintf(str, "%d", n + 1);
		memset(cnt, 0, sizeof cnt);
		for(int i = 1; i < len; ++i)
			for(int j = 0; j < 1 << maxd; ++j)
				cnt[j] += f[i][j];
		for(int i = 0, mask = 0; i < len; mask |= 1 << (str[i++] - '0'))
			for(int j = mask ? 0 : 1; '0' + j < str[i]; ++j)
				for(int k = 0; k < 1 << maxd; ++k)
					cnt[mask | (1 << j) | k] += g[len - 1 - i][k];
		ans = mod - 1;
		dfs(0);
		printf("Case %d: %d\n", Case, ans);
	}
	return 0;
}
