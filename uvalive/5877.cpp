#include <cmath>
#include <cstdio>
#include <cstring>
const int maxn = 1010, INF = 0x3f3f3f3f;
const double eps = 1e-8;
int t, n, s, f, e[maxn][maxn], dis[maxn], que[maxn], L, R;
long long x[maxn], y[maxn];
double l1, l2;
bool vis[maxn];
int dcmp(double x)
{
	return (x > eps) - (x < -eps);
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d%lf%lf", &n, &s, &f, &l1, &l2);
		for(int i = 1; i <= n; ++i)
			scanf("%lld%lld", x + i, y + i);
		for(int i = 1; i <= n; ++i)
		{
			e[i][0] = 0;
			for(int j = 1; j <= n; ++j)
				if(i != j && (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]) <= (l1 + l2) * (l1 + l2))
					e[i][++e[i][0]] = j;
		}
		L = R = 0;
		memset(vis, 0, sizeof vis);
		memset(dis, 0x3f, sizeof dis);
		que[R++] = s;
		dis[s] = 0;
		while(L < R)
		{
			int u = que[L++];
			for(int i = 1; i <= e[u][0]; ++i)
			{
				int &v = e[u][i];
				if(!vis[v])
				{
					dis[v] = dis[u] + 1;
					que[R++] = v;
					vis[v] = 1;
				}
			}
		}
		if(dis[f] == INF)
			puts("Impossible");
		else
			printf("%d\n", dis[f]);
	}
	return 0;
}
