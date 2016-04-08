#include <cstdio>
typedef long long LL;
const int maxp = 1001, maxs = 8, maxd = 50, mod = 1000000007;
int tot, prime[maxp], n, k, top, stack[maxs], ans;
LL now = 1, INF;
bool vis[maxp];
inline LL calc(LL x, const int &pr)
{
	LL cnt = 0;
	for(x /= pr; x; x /= pr)
		cnt += x;
	return cnt;
}
inline void check(LL L, const int &pr, const LL &cn)
{
	if(calc(L, pr) >= cn)
		return;
	int len = 0;
	LL f[maxd] = {1}, g[maxd] = {0}, h[maxd] = {0}, ret = 0, tmp = cn;
	for(int i = 1; i < maxd; ++i)
	{
		f[i] = f[i - 1] * pr;
		g[i] = g[i - 1] + f[i - 1];
		h[i] = h[i - 1] + g[i] * (pr - 1);
		if(h[i] >= tmp)
		{
			len = i;
			break;
		}
	}
	for(int i = len; i; --i)
	{
		LL temp = tmp - (i ? h[i - 1] : 0);
		if(temp <= 0)
			continue;
		int val = (temp - 1) / g[i] + 1;
		ret += val * f[i];
		tmp -= val * g[i];
	}
	//printf("%d %d : %lld\n", pr, cn, ret);
	if(now < ret)
	    now = ret;
	/*++L;
	LL R = INF;
	while(L < R)
	{
		LL M = L + R >> 1;
		if(calc(M, pr) >= cn)
			R = M;
		else
			L = M + 1;
	}
	if(now < L)
	    now = L;*/
}
int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 2; i < maxp; ++i)
	{
		if(!vis[i])
			prime[tot++] = i;
		for(int j = 0, o; j < tot && (o = i * prime[j]) < maxp; ++j)
		{
			vis[o] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	for(int i = 2; i <= n; ++i)
	{
	    INF = (LL)i * k;
		int x = i;
		for(int j = 0; j < tot && prime[j] * prime[j] <= x; ++j)
			if(x % prime[j] == 0)
			{
				for( ; x % prime[j] == 0; x /= prime[j]);
				stack[top++] = prime[j];
			}
		if(x > 1)
			stack[top++] = x;
		if(i <= k)
    		for(int &j = top; j; --j)
    			check(now, stack[j - 1], calc(i, stack[j - 1]) * k);
    	else
    	{
    	    for(int j = 0; j < top; ++j)
    			check(now, stack[j], calc(i, stack[j]) * k);
    		top = 0;
    	}
    	ans = (ans + now) % mod;
	}
	printf("%d\n", ans);
	return 0;
}
