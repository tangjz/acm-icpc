#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 151, maxv = 501;
struct edge
{
	int to, lon, lim;
};
int n, m, d, pre[maxn * maxv], ans[maxn];
double dis[maxn * maxv];
vector<edge> e[maxn];
priority_queue<pair<double, int>, vector<pair<double, int> >, greater<pair<double, int> > > Q;
bool vis[maxn * maxv];
int main()
{
	scanf("%d%d%d", &n, &m, &d);
	for(int i = 0; i < n; ++i)
		for(int j = 1; j < maxv; ++j)
			dis[i * maxv + j] = 1e10;
	while(!Q.empty())
		Q.pop();
	while(m--)
	{
		int x, y, l, v;
		scanf("%d%d%d%d", &x, &y, &v, &l);
		e[x].push_back((edge){y, l, v});
	}
	dis[70] = 0;
	Q.push(make_pair(dis[70], 70));
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
				pre[nxt] = now;
				dis[nxt] = dis[now] + (double)w / t;
				Q.push(make_pair(dis[nxt], nxt));
			}
		}
	}
	int pos = d * maxv + 1;
	for(int i = 2; i < maxv; ++i)
		if(dis[pos] > dis[d * maxv + i])
			pos = d * maxv + i;
	for(ans[0] = 0; pos; pos = pre[pos])
		ans[++ans[0]] = pos / maxv;
	for(int i = ans[0]; i; --i)
		printf("%d%c", ans[i], " \n"[i == 1]);
	return 0;
}
