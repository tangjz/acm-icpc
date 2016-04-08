#include <cstdio>
#include <cstring>
const int maxn = 210;
int n, f[maxn], tot, cir[maxn], cnt[maxn], vis[maxn], dis[maxn], dfsno;
bool incir[maxn];
long long gcd(long long x, long long y)
{
	return y ? gcd(y, x % y) : x;
}
int gcd(int x, int y)
{
	return y ? gcd(y, x % y) : x;
}
/*int gcd(BigInt x, int y)
{
	BigInt tmp = x - (x / y) * y;
	int rev = tmp.num[0];
	return gcd(y, rev);
}*/
void dfs(int u)
{
	vis[u] = dfsno;
	if(!vis[f[u]])
	{
		dfs(f[u]);
		if(!incir[u])
			dis[u] = dis[f[u]] + 1;
	}
	else if(vis[f[u]] == dfsno)
	{
		cir[u] = ++tot;
		++cnt[tot];
		incir[u] = 1;
		for(int i = f[u], last = u; i != u; last = i, i = f[i])
		{
			cir[i] = cir[last];
			++cnt[tot];
			incir[i] = 1;
		}
	}
	else if(!incir[u])
		dis[u] = dis[f[u]] + 1;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", f + i);
	for(int i = 1; i <= n; ++i)
		if(!vis[i])
		{
			++dfsno;
			dfs(i);
		}
	long long ans = 1;
	//BigInt ans = 1;
	for(int i = 1; i <= tot; ++i)
	{
		int rev = gcd(ans, (long long)cnt[i]);
		ans = ans * cnt[i] / rev;
	}
	long long minans = 0;
	for(int i = 1; i <= n; ++i)
		if(minans < dis[i])
			minans = dis[i];
	//BigInt tmp = {};
	//tmp.getint(minans);
	//if(tmp > ans)
	if(minans > ans)
		ans = ((minans - 1) / ans + 1) * ans;
		//ans = ((tmp - 1) / ans + 1) * ans;
	printf("%lld\n", ans);
	//ans.print();
	return 0;
}
