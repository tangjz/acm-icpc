#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 233, maxv = 233;
struct edge
{
	int to, lon, lim;
};
int t, n, m;
double dis[maxn * maxv];
vector<edge> e[maxn];
priority_queue<pair<double, int>, vector<pair<double, int> >, greater<pair<double, int> > > Q;
bool vis[maxn * maxv];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		memset(vis, 0, sizeof vis);
		for(int i = 0; i < n; ++i)
		{
			e[i].clear();
			for(int j = 0; j < maxv; ++j)
				dis[i * maxv + j] = 1e10;
		}
		while(!Q.empty())
			Q.pop();
		for(int i = 0; i < m; ++i)
		{
			int x, y, l, v;
			scanf("%d%d%d%d", &x, &y, &l, &v);
			e[--x].push_back((edge){--y, l, v});
		}
		dis[61] = 0;
		Q.push(make_pair(dis[61], 61));
		while(!Q.empty())
		{
			int now = Q.top().second;
			Q.pop();
			if(vis[now])
				continue;
			vis[now] = 1;
			int u = now / maxv, lim = now % maxv;
			for(vector<edge>::iterator it = e[u].begin(); it != e[u].end(); ++it)
			{
				int &v = it -> to, &w = it -> lon, &t = !(it -> lim) ? lim : it -> lim;
				int nxt = v * maxv + t;
				if(dis[nxt] > dis[now] + (double)w / t)
				{
					dis[nxt] = dis[now] + (double)w / t;
					Q.push(make_pair(dis[nxt], nxt));
				}
			}
		}
		double ans = 1e10;
		for(int i = 0; i < maxv; ++i)
			if(ans > dis[(n - 1) * maxv + i])
				ans = dis[(n - 1) * maxv + i];
		printf("%.4f\n", ans);
	}
	return 0;
}
