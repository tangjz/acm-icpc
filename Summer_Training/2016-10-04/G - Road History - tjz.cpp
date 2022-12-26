#include <stdio.h>
#include <algorithm>
typedef long long LL;
const int maxn = 100001;
int n, m, dsu[maxn], dis[maxn], cnt[maxn][2];
bool vis[maxn];
LL ans;
int find(int x)
{
	if(dsu[x] < 0)
		return x;
	int tmp = dsu[x];
	dsu[x] = find(dsu[x]);
	dis[x] ^= dis[tmp];
	return dsu[x];
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
	{
		dsu[i] = -1;
		dis[i] = 0;
		cnt[i][0] = 1;
	}
	while(m--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		int x = find(u), y = find(v);
		if(x != y)
		{
			ans -= vis[x] ? cnt[x][0] * (cnt[x][0] - 1LL) >> 1 : (LL)cnt[x][0] * cnt[x][1];
			ans -= vis[y] ? cnt[y][0] * (cnt[y][0] - 1LL) >> 1 : (LL)cnt[y][0] * cnt[y][1];
			if(dsu[x] > dsu[y])
			{
				std::swap(x, y);
				std::swap(u, v);
			}
			if(dsu[x] == dsu[y])
				--dsu[x];
			dsu[y] = x;
			vis[x] |= vis[y];
			if(!vis[x])
			{
				dis[y] = dis[u] ^ dis[v] ^ 1;
				cnt[x][0] += cnt[y][dis[y]];
				cnt[x][1] += cnt[y][dis[y] ^ 1];
				cnt[y][0] = cnt[y][1] = 0;
			}
			else
			{
				int tmp = cnt[x][0] + cnt[x][1] + cnt[y][0] + cnt[y][1];
				cnt[x][0] = tmp;
				cnt[x][1] = 0;
			}
			ans += vis[x] ? cnt[x][0] * (cnt[x][0] - 1LL) >> 1 : (LL)cnt[x][0] * cnt[x][1];
		}
		else if(!vis[x] && dis[u] == dis[v])
		{
			ans -= (LL)cnt[x][0] * cnt[x][1];
			cnt[x][0] += cnt[x][1];
			cnt[x][1] = 0;
			vis[x] = 1;
			ans += cnt[x][0] * (cnt[x][0] - 1LL) >> 1;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
