#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef struct { int a, b, d; } Limit;
const int maxn = 55;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
int t, n, m1, m2, delta;
Limit lim[maxn << 1];
LL dis[maxn][maxn << 1], Max, Min, ans;
void upd(int v, int u, int k, int b)
{
	for(int i = max(-delta, -delta - k); max(i + k, i) <= delta; ++i)
		if(dis[u][i + delta] != INF && dis[v][i + k + delta] > dis[u][i + delta] + b)
			dis[v][i + k + delta] = dis[u][i + delta] + b;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d", &n, &m1, &m2);
		for(int i = 0; i < m1 + m2; ++i)
			scanf("%d%d%d", &lim[i].a, &lim[i].b, &lim[i].d);
		delta = n + 1;
		Max = INF;
		Min = n;
		ans = -1;
		for(int s = 0; s <= n; ++s)
		{
			memset(dis, 0x3f, sizeof dis);
			dis[s][delta] = 0;
			for(int tt = 0; tt < delta; ++tt)
			{
				for(int i = 0; i < n; ++i)
					upd(i, i + 1, 0, -1);
				upd(0, n, -1, 0);
				upd(n, 0, 1, 0);
				for(int i = 0; i < m1; ++i)
					upd(lim[i].a, lim[i].b, lim[i].a > lim[i].b, -lim[i].d);
				for(int i = m1; i < m1 + m2; ++i)
					upd(lim[i].b, lim[i].a, -(lim[i].a > lim[i].b), lim[i].d);
			}
			for(int i = -delta; i < 0; ++i)
				if(dis[s][i + delta] != INF && Max > -dis[s][i + delta] / i)
					Max = -dis[s][i + delta] / i;
			for(int i = 1; i <= delta; ++i)
				if(dis[s][i + delta] != INF && Min < (-dis[s][i + delta] - 1) / i + 1)
					Min = (-dis[s][i + delta] - 1) / i + 1;
			if(dis[s][delta] < 0 || Max < Min)
			{
				ans = 0;
				break;
			}
		}
		if(ans == -1 && Max != INF)
			ans = Max - Min + 1;
		printf("%lld\n", ans);
	}
	return 0;
}
