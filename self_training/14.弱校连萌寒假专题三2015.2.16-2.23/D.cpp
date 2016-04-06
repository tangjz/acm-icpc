#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;
const int maxp = 10001, maxn = 211, INF = 0x3f3f3f3f;
int tot, prime[maxp], n, c[maxn], num, f[maxp], pre[maxp], ans[maxp];
bool vis[maxp];
int main()
{
	vis[1] = 1;
	for(int i = 2; i < maxp; ++i)
	{
		if(!vis[i])
		{
			prime[tot++] = i;
			if(!vis[tot])
				c[n++] = i;
		}
		for(int j = 0; j < tot && i * prime[j] < maxp; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	memset(f, 0x3f, sizeof f);
	f[0] = 0;
	for(int i = 3; i < maxp; ++i)
		for(int j = 0; j < n; ++j)
			if(i < c[j])
				break;
			else if(f[i] > f[i - c[j]] + 1)
			{
				pre[i] = i - c[j];
				f[i] = f[i - c[j]] + 1;
			}
	f[0] = INF;
	while(scanf("%d", &n) != EOF)
	{
		if(f[n] == INF)
		{
			puts("0");
			continue;
		}
		for(int i = 0, now = n; now > 0; ++i, now = pre[now])
			ans[i] = now - pre[now];
		sort(ans, ans + f[n], greater<int>());
		printf("%d\n", f[n]);
		for(int i = 0; i < f[n]; ++i)
			printf("%d%c", ans[i], " \n"[i == f[n] - 1]);
	}
	return 0;
}
