/*
 * 先枚举一部分质数 然后二分答案，容斥检查 问的东西只是和2986相反罢了
 */
#include <cstdio>
typedef long long LL;
int n, tot, p[4444];
bool vis[41000];
LL dfs(int dep, int b, int lef)
{
	LL o = dep & 1 ? 1 : -1, ans = 0;
	for(int i = b; i <= tot; ++i)
		if(p[i] * p[i] > lef) break;
		else ans += lef / (p[i] * p[i]) * o + dfs(dep + 1, i + 1, lef / (p[i] * p[i]));
	return ans;
}
int main()
{
	for(int i = 2; i < 41000; ++i)
		if(!vis[i])
		{
			p[++tot] = i;
			for(int j = i; j <= 41000 / i; ++j) vis[i * j] = 1;
		}
	int t;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		int l = 1, r = 1644934081, m, tmp;
		while(l < r)
		{
			m = (LL)l + r >> 1;
			tmp = m - dfs(1, 1, m);
			if(tmp < n) l = m + 1;
			else r = m;
		}
		printf("%d\n", l);
	}
	return 0;
}
