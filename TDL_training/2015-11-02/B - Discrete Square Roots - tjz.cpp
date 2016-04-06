#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 32000, maxs = 10, maxm = 1 << 12;
int tot, prime[maxn], n, xx, r0, cnt, p[maxs], c[maxs], sum, ans[maxm];
bool vis[maxn];
int exgcd(int a, int b, int &x, int &y)
{
	if(!b)
	{
		x = 1;
		y = 0;
		return a;
	}
	int r = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return r;
}
void dfs(int dep, int now)
{
	if(dep == cnt)
	{
		int &a = now, b = n / a, x, y, r = exgcd(a, b, x, y);
		if((2 * r0) % r)
			return;
		x = 2 * r0 / r * (LL)x % (b / r);
		if(x < 0)
			x += b / r;
		int r1 = (a * x - r0) % (n / r);
		if(r1 < 0)
			r1 += n / r;
		for( ; r1 < n; r1 += n / r)
			ans[sum++] = r1;
		return;
	}
	dfs(dep + 1, now);
	for(int i = 1; i <= c[dep]; ++i)
		dfs(dep + 1, now *= p[dep]);
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
	for(int Case = 1; scanf("%d%d%d", &xx, &n, &r0) == 3 && xx + n + r0; ++Case)
	{
		cnt = sum = 0;
		int tmp = n;
		for(int i = 0; i < tot && prime[i] * prime[i] <= tmp; ++i)
			if(tmp % prime[i] == 0)
			{
				for(c[cnt] = 0; tmp % prime[i] == 0; tmp /= prime[i], ++c[cnt]);
				p[cnt++] = prime[i];
			}
		if(tmp > 1)
		{
			c[cnt] = 1;
			p[cnt++] = tmp;
		}
		ans[sum++] = r0;
		dfs(0, 1);
		//printf("%d\n", sum);
		sort(ans, ans + sum);
		sum = unique(ans, ans + sum) - ans;
		//printf("%d\n", sum);
		printf("Case %d: ", Case);
		for(int i = 0; i < sum; ++i)
			printf("%d%c", ans[i], " \n"[i == sum - 1]);
	}
	return 0;
}
