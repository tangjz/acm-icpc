/*
 * 先枚举一部分 然后容斥 
 */ 
#include <cstdio>
int tot;
long long n, p[80001];
bool vis[1000001];
long long dfs(int dep, int b, long long lef)
{
	long long o, ans = 0;
	o = dep & 1 ? 1 : -1;
	for(int i = b; i <= tot; ++i)
		if((long long)p[i] * p[i] > lef) break;
		else ans += lef / (p[i] * p[i]) * o + dfs(dep + 1, i + 1, lef / (p[i] * p[i]));
	return ans;
}
int main()
{
	for(int i = 2; i < 1000000; ++i)
		if(!vis[i])
		{
			p[++tot] = i;
			for(int j = i; j <= 1000000 / i; ++j) vis[i * j] = 1;
		}
	scanf("%lld", &n);
	long long l = 1, r = 100000000000ll, m, tmp;
	while(l < r)
	{
		m = l + r >> 1;
		tmp = dfs(1, 1, m);
		if(tmp < n) l = m + 1;
		else r = m;
	}
	printf("%lld\n", l);
	return 0;
}
