#include <queue>
#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
typedef pair<int, int> edge;
const int maxd = 4, dx[maxd] = {0, 1, 0, -1}, dy[maxd] = {1, 0, -1, 0};
const int maxn = 101, maxs = 10001, maxo = 100001, maxv = 10, INF = 0x3f3f3f3f;
priority_queue<edge, vector<edge>, greater<edge> > Q;
int t, n, m, S, T, dis[maxo], sum, ans;
char buf[maxn][maxn];
bool vis[maxo];
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d%d", &n, &m);
		sum = 0;
		for(int i = 0; i < n; ++i)
		{
			scanf("%s", buf[i]);
			for(int j = 0; j < m; ++j)
			{
				if(buf[i][j] == 'A')
				{
					S = i * m + j;
					buf[i][j] = '1';
				}
				else if(buf[i][j] == 'B')
				{
					T = i * m + j;
					buf[i][j] = '1';
				}
				sum += buf[i][j] - '0';
			}
		}
		for( ; !Q.empty(); Q.pop());
		memset(dis, 0x3f, sizeof dis);
		memset(vis, 0, sizeof vis);
		int SS = S * maxv + 1;
		dis[SS] = 1;
		Q.push(make_pair(dis[SS], SS));
		while(!Q.empty())
		{
			int u = Q.top().second;
			Q.pop();
			if(vis[u])
				continue;
			vis[u] = 1;
			int ux, uy, uk;
			uy = u / maxv;
			uk = u % maxv;
			ux = uy / m;
			uy = uy % m;
			for(int d = 0; d < maxd; ++d)
			{
				int vx = ux + dx[d], vy = uy + dy[d];
				if(vx < 0 || vx >= n || vy < 0 || vy >= m || buf[vx][vy] == '0')
					continue;
				int w = buf[vx][vy] - '0', vk = max(uk, w), v = (vx * m + vy) * maxv + vk;
				if(dis[v] > dis[u] + w)
				{
					dis[v] = dis[u] + w;
					Q.push(make_pair(dis[v], v));
				}
			}
		}
		ans = 0;
		for(int i = 1; i < maxv; ++i)
		{
			int idx = T * maxv + i;
			if(dis[idx] == INF)
				continue;
			int tmp = sum - dis[idx] + i;
			if(ans < tmp)
				ans = tmp;
		}
		printf("Case #%d: %d\n", Case, ans);
	}
	return 0;
}
