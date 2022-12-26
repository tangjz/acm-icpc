#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100001, maxm = 1000001;
int n, m, tot, pre[maxn], que[maxn], L, R, dis[maxn], sum, ans;
bool vis[maxn];
struct Edge
{
	int nxt, v, w;
} e[maxm << 1];
int main()
{
	scanf("%d%d", &n, &m);
	while(m--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[++tot] = (Edge){pre[u], v, 1};
		pre[u] = tot;
		e[++tot] = (Edge){pre[v], u, -1};
		pre[v] = tot;
	}
	for(int i = 1; i <= n; ++i)
		if(!vis[i])
		{
			int Max = 0, Min = 0;
			que[R++] = i;
			vis[i] = 1;
			while(L < R)
			{
				int &u = que[L++];
				for(int it = pre[u]; it; it = e[it].nxt)
				{
					int &v = e[it].v, &w = e[it].w;
					if(vis[v])
						ans = __gcd(ans, abs(dis[u] + w - dis[v]));
					else
					{
						que[R++] = v;
						vis[v] = 1;
						dis[v] = dis[u] + w;
						if(Max < dis[v])
							Max = dis[v];
						if(Min > dis[v])
							Min = dis[v];
					}
				}
			}
			sum += Max - Min + 1;
		}
	if(ans && ans < 3)
		puts("-1 -1");
	else if(ans)
	{
		for(int i = 3; ; ++i)
			if(ans % i == 0)
			{
				printf("%d %d\n", ans, i);
				break;
			}
	}
	else if(sum < 3)
		puts("-1 -1");
	else
		printf("%d %d\n", sum, 3);
	return 0;
}
